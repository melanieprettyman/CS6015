#include "droplet.h"
#include <QPixmap>
#include <QUrl>
#include <QMediaPlayer>



droplet::droplet(Difficulty difficulty): dropletSpeed(100) {
    setPixmap(QPixmap(":/images/diamond.png").scaled(40,40));
    dropTimer = new QTimer(this);
    connect(dropTimer, &QTimer::timeout, this, &droplet::moveDroplet);

    //music
    collectSound.setSource(QUrl("qrc:/sounds/62997__radian__chime-0020.wav"));
    collectSound.setVolume(0.7);
    stinkySound.setSource(QUrl("qrc:/sounds/50924__rutgermuller__vocal-man-hit-ohhh.wav"));
    stinkySound.setVolume(1);









    // Adjust droplet speed based on difficulty level
    switch (difficulty) {
    case Easy:
        dropletSpeed = 10;
        break;
    case Medium:
        dropletSpeed = 50;
        break;
    case Hard:
        dropletSpeed = 100;
        break;
    default:
        dropletSpeed = 10; // Default to easy difficulty
    }
    dropTimer->start(500);

}
QTimer* droplet::getTimer()const{
    return dropTimer;
}
void droplet::moveDroplet(){
    if(isPaused()){
        return;
    }
    setPos(x(),y() + dropletSpeed);
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    foreach (QGraphicsItem* item, collidingItemsList)
    {
        if (dynamic_cast<bucket*>(item))
        {
            emit collide();
            collectSound.play();
            delete this;
            return;
        }
    }
    if(this->y() > 700){
        emit damageCounter();
        stinkySound.play();
        delete this;
    }
}


void droplet::updateSpeed(){
    dropletSpeed *= 1.2;
}

void droplet::pause(){
    if(dropTimer->isActive()){
        dropTimer->stop();
    }
}

bool droplet::isPaused(){
    return !dropTimer->isActive();
}
