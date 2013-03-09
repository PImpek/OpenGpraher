/* Copyright (c) 2013, Bartosz Foder, (bartosz@foder.pl)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "addcurvedialog.h"
#include "ui_addcurvedialog.h"

AddCurveDialog::AddCurveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCurveDialog)
{
    ui->setupUi(this);

    this->connect(this->ui->openFIle,SIGNAL(clicked()),this,SLOT(openFile()));
    this->connect(this->ui->file,SIGNAL(textChanged(QString)),this,SLOT(loadFile()));
    this->connect(this->ui->delsign,SIGNAL(textChanged(QString)),this,SLOT(loadFile()));

    this->connect(this->ui->delws,SIGNAL(toggled(bool)),this,SLOT(loadFile()));
    this->connect(this->ui->decpointculture,SIGNAL(toggled(bool)),this,SLOT(loadFile()));
    this->connect(this->ui->useHeaders,SIGNAL(toggled(bool)),this,SLOT(loadFile()));
}

AddCurveDialog::~AddCurveDialog()
{
    delete ui;
}

Curve *AddCurveDialog::getCurve()
{
    if(this->ui->file->text().isEmpty()) return nullptr;

    auto c = new Curve();
    c->setLabel(std::string(this->ui->file->text().split("/").takeLast().toUtf8().constData()));

    for (int i = 0 ; i< this->ui->dataTable->rowCount();i++)
    {
        bool convOk[3] = {true,true,true};
        double x,y;
        std::vector<double> extraData = std::vector<double>();

        y = this->ui->dataTable->item(i,this->ui->ycol->value()-1)->text().toDouble(&convOk[0]);
        x = this->ui->dataTable->item(i,this->ui->xcol->value()-1)->text().toDouble(&convOk[1]);

        if(this->ui->useExtraData->isChecked())
        {
            for(int j = 0 ; j < this->ui->dataTable->colorCount() ; j++)
            {
                if ((j != this->ui->ycol->value()-1)&&(j != this->ui->xcol->value()-1))
                    extraData.push_back(this->ui->dataTable->item(i,this->ui->xcol->value()-1)->text().toDouble(&convOk[2]));
            }
        }

        if(this->ui->nancut->isChecked() && convOk[0] && convOk[1] && convOk[2] )
        {
            continue;
        }

        auto row = std::make_tuple(x,y,extraData);
        c->getData()->push_back(row);
    }

    c->setComment(std::string("Created from "+std::string(this->ui->file->text().toUtf8().constData())+"\n"+
                              "on "+std::string(QDateTime::currentDateTime().toString().toUtf8().constData())));

    return c;
}

void AddCurveDialog::openFile()
{
    QString fname =  QFileDialog::getOpenFileName(this,"Open Data from file",
                                                  QString()," Comma Separated Values (*.csv)");
    this->ui->file->setText(fname);
}

void AddCurveDialog::loadFile()
{
    QString line,fname = this->ui->file->text();
    int numOfCols = -1;

    if (!fname.isNull())
    {
        QFile file(fname,this);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                 return;

        QTextStream st(&file);
        //headers
        if (this->ui->useHeaders->isChecked())
        {
            line = st.readLine();

            auto headers = (this->ui->delws->isChecked())?
                        line.split(QRegExp("\\s+")):
                        line.split(this->ui->delsign->text());
            numOfCols = headers.count();

            this->ui->dataTable->setColumnCount(numOfCols);
            this->ui->dataTable->setHorizontalHeaderLabels(headers);
        }
        this->ui->dataTable->setRowCount(0);
        line = st.readLine();
        while (!line.isNull())
        {
            auto lvec = this->parseLine(line);
            if (numOfCols < 0){
                numOfCols = lvec->size();
                this->ui->dataTable->setColumnCount(numOfCols);
            }

            this->ui->dataTable->setRowCount(this->ui->dataTable->rowCount()+1);
            for(int i = 0; i <numOfCols;i++)
            {

                    this->ui->dataTable->setItem(this->ui->dataTable->rowCount()-1,i,(i<lvec->size()&&(!std::isnan(lvec->at(i))))?
                                                 new QTableWidgetItem(QString::number(lvec->at(i))):
                                                 new QTableWidgetItem("NaN"));
                    this->ui->dataTable->verticalHeader()->resizeSection(this->ui->dataTable->rowCount()-1,17);
            }


            line = st.readLine();
        }

        this->ui->groupBox->setEnabled(true);
        this->ui->xcol->setMaximum(numOfCols);
        this->ui->ycol->setMaximum(numOfCols);
    }

}

std::vector<double> *AddCurveDialog::parseLine(QString line)
{
    auto vec = new std::vector<double>();

    auto  chunks = line.split((this->ui->delws->isChecked())?"\\s+":this->ui->delsign->text());
    bool depOnCulture = this->ui->decpointculture->isChecked();

    std::for_each(chunks.begin(),chunks.end(),[vec,&depOnCulture](QString ch){
        bool convOk;
        double d;

        if (depOnCulture)
        {
            d = ch.toDouble(&convOk);
        } else {
            QLocale c(QLocale::C);
            d = c.toDouble(ch,&convOk);
        }
        vec->push_back((convOk)?d:NAN);
    });

    return vec;
}
