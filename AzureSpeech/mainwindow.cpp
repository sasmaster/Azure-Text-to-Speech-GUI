#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),mIsConnected(false)
{
    ui->setupUi(this);
 //  QVariant v;v.setValue("Aral sdf");
    ui->voicesBox->addItem("English(female),Aria Neural",QVariant("en-US-AriaNeural"));
    ui->voicesBox->addItem("Hebrew(female),Hila Neural",QVariant("he-IL-HilaNeural"));
    ui->voicesBox->addItem("Hebrew,Avri Neural",QVariant("he-IL-AvriNeural"));



    connect(ui->connectBut, &QPushButton::clicked, this, &MainWindow::HandleConnectionATTS);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::TextToSpeech);

    statusBar()->show();
}

void MainWindow::HandleConnectionATTS()
{
    if(mIsConnected)
    {
        //destroy
        mATTSSynthesizer.reset();
        mATTSAudioConfig.reset();
        mATTSConfig.reset();
        ui->connectBut->setText("Connect");
        mIsConnected = false;
    }else
    {
      // make sure you got TTS serivice key and region right (See Azure Cognitive services setup)
        const auto key = ui->serviceKeyTextEdit->text().toStdString();
        const auto region = ui->regionTextEdit->text().toStdString();
        mATTSConfig = SpeechConfig::FromSubscription(key,region);
        mATTSAudioConfig = AudioConfig::FromWavFileOutput("file.wav");
        mATTSSynthesizer = SpeechSynthesizer::FromConfig(mATTSConfig, mATTSAudioConfig);


        ui->connectBut->setText("Disconnect");
        mIsConnected = true;
    }


}

void MainWindow::TextToSpeech()
{

    if(ui->textToSpeechEdit->document()->isEmpty())
    {
        return;
    }



    try {
        ui->processButton->setEnabled(false);

        // Sets the voice name.
        // e.g. "Microsoft Server Speech Text to Speech Voice (en-US, AriaRUS)".
        // The full list of supported voices can be found here:
        // https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support
        auto selectedValue = ui->voicesBox->itemData(ui->voicesBox->currentIndex()).toString();
        mATTSConfig->SetSpeechSynthesisVoiceName(selectedValue.toStdString());

        mATTSSynthesizer = SpeechSynthesizer::FromConfig(mATTSConfig,mATTSAudioConfig);//if no other audio config provided into second param,will output the sound into speakers (at least on windows)

        auto wideStr = ui->textToSpeechEdit->toPlainText().toStdWString();
        auto result = mATTSSynthesizer->SpeakTextAsync(wideStr).get();
       // auto result = mATTSSynthesizer->SpeakText(wideStr); //sync mode
        /*
        while(true)
        {

            if(result->Reason == ResultReason::SynthesizingAudioCompleted)
            {
                break;
            }
        }
      */


        ui->processButton->setEnabled(true);
    }
    catch (std::exception e)
    {
        statusBar()->showMessage(e.what());

        return;

    }

    ui->processButton->setEnabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}
