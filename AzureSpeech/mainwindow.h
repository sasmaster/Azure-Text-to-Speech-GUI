#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "speechapi_cxx.h"

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<SpeechConfig> mATTSConfig;
    std::shared_ptr<AudioConfig> mATTSAudioConfig;
    std::shared_ptr<SpeechSynthesizer> mATTSSynthesizer;
    bool mIsConnected;
private slots:
    void HandleConnectionATTS();

    void TextToSpeech();

};

#endif // MAINWINDOW_H
