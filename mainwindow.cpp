#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)  : QMainWindow(parent) , ui(new Ui::MainWindow),finding_match(false)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerTick()));
    this->setupGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: setupGame(){
    int index;
    QString nextEmoji;
    QList<QString> * animalEmoji = new QList<QString>(std::initializer_list<QString>{
                                                         "😇","😇",
                                                         "🥰","🥰",
                                                         "🐥","🐥",
                                                         "🥑","🥑",
                                                         "😈","😈",
                                                         "🙄","🙄",
                                                         "👀","👀",
                                                         "🥳","🥳"
                                                     });

    for(auto button: this->findChildren<QPushButton *>()){
        button->setVisible(true);
        index = rand() % animalEmoji->count();
        nextEmoji=(*animalEmoji)[index];
        button->setText(nextEmoji);
        animalEmoji->removeAt(index);

        connect(button, SIGNAL(clicked()),this ,SLOT(ButtonClicked()));
    }
    timer->start();
    tenthsOfSecondsElapsed=0;
    matchesFound=0;
    delete animalEmoji;
}
void MainWindow::TimerTick(){
    tenthsOfSecondsElapsed++;
    ui->label->setText(QString::number(tenthsOfSecondsElapsed/10.0F,'f',1));

    if(matchesFound==8){
        timer->stop();
        ui->label->setText("Your time: "+ QString::number(tenthsOfSecondsElapsed/10.0F,'f',1)+" seconds");
    }
}

void MainWindow::ButtonClicked(){
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    if(finding_match==false){
        button->setVisible(false);
        lastEmojiClicked=button;
        finding_match=true;
    }
    else if (button->text()==lastEmojiClicked->text()){
        button->setText("✅");
        lastEmojiClicked->setVisible(true);
        lastEmojiClicked->setText("✅");
        finding_match=false;
        matchesFound++;
    }
    else{
        lastEmojiClicked->setVisible(true);
        finding_match = false;
    }
}
