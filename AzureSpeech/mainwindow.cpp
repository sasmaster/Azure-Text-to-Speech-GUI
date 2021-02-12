#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVariant>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),mIsConnected(false)
{
    ui->setupUi(this);
    setWindowTitle("Azure TTS Tool, V - 0.1");

   //https://docs.microsoft.com/en-us/azure/cognitive-services/speech-service/language-support
    ui->voicesBox->addItem("English US(female),Aria Neural",QVariant("en-US-AriaNeural"));
    ui->voicesBox->addItem("English US(female),Jenny Neural",QVariant("en-US-JennyNeural"));
    ui->voicesBox->addItem("English US(male),Guy Neural",QVariant("en-US-GuyNeural"));
    ui->voicesBox->addItem("English GB(female),Libby Neural",QVariant("en-GB-LibbyNeural"));
    ui->voicesBox->addItem("English US(female),Aria",QVariant("en-US-AriaRUS"));
    ui->voicesBox->addItem("English US(female),Zira",QVariant("en-US-ZiraRUS"));


    ui->voicesBox->addItem("Hebrew(female),Hila Neural",QVariant("he-IL-HilaNeural"));
    ui->voicesBox->addItem("Hebrew(Male),Avri Neural",QVariant("he-IL-AvriNeural"));
    ui->voicesBox->addItem("Hebrew(Male),Asaf",QVariant("he-IL-Asaf"));



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
        std::string userKeyString;
        if(ui->serviceKeyTextEdit->text().size() == 0)
        {
            QFile file(QCoreApplication::applicationDirPath() + "/key.txt");
            if(!file.open(QIODevice::ReadOnly))
            {
                 statusBar()->showMessage("Failed to load  user key from file");
                return;
            }
            QTextStream in(&file);
            userKeyString = in.readLine().toStdString();

        }else
        {
            userKeyString = ui->serviceKeyTextEdit->text().toStdString();
        }
      // make sure you got TTS serivice key and region right (See Azure Cognitive services setup)

        const auto region = ui->regionTextEdit->text().toStdString();
        mATTSConfig = SpeechConfig::FromSubscription(userKeyString,region);

      //  mATTSSynthesizer = SpeechSynthesizer::FromConfig(mATTSConfig, mATTSAudioConfig);


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
         ui->processButton->setText("Working...");

        QApplication::processEvents();
        // Sets the voice name.
        // e.g. "Microsoft Server Speech Text to Speech Voice (en-US, AriaRUS)".
        // The full list of supported voices can be found here:
        // https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support
        auto selectedValue = ui->voicesBox->itemData(ui->voicesBox->currentIndex()).toString();

        mATTSConfig->SetSpeechSynthesisVoiceName(selectedValue.toStdString());
        mATTSAudioConfig = AudioConfig::FromWavFileOutput(ui->filePathTextEdit->text().toStdString());

        //if no other audio config provided into second param,will output the sound into speakers (at least on windows)
        if(ui->toSpeakersCheckBox->isChecked())
        {
             mATTSSynthesizer = SpeechSynthesizer::FromConfig(mATTSConfig);
        }else
        {
             mATTSSynthesizer = SpeechSynthesizer::FromConfig(mATTSConfig,mATTSAudioConfig );
        }


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

        ui->processButton->setText("Process");
        ui->processButton->setEnabled(true);
    }
    catch (std::exception e)
    {
        statusBar()->showMessage(e.what());
        ui->processButton->setText("Process");
        ui->processButton->setEnabled(true);
        return;

    }

    ui->processButton->setEnabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}
