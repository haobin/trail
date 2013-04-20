// Navigation pane project template
#include "Trail.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

using namespace bb::cascades;

Trail::Trail(bb::cascades::Application *app) :
    QObject(app),
    mStarted(false),
    mGpsLocation()
{
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    registerContext(qml);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

void Trail::registerContext(QmlDocument *qml)
{
    QDeclarativeContext *rootContext = qml->documentContext()->engine()->rootContext();
    if (NULL == rootContext) {
        qWarning("rootContext is null!");
        return;
    }
    rootContext->setContextProperty("Trail", this);
    rootContext->setContextProperty("GpsLocation", &mGpsLocation);

    // find ref to mapview
//    AbstractPane *root = qml->createRootObject<AbstractPane>();
//    root->
}


bool Trail::isStarted() const
{
    return mStarted;
}

void Trail::setStarted(bool started)
{
    if (started != mStarted) {
        mStarted = started;
        Q_EMIT startedChanged();
    }
}

void Trail::startWorkout()
{
    qDebug("start work out");
    setStarted(true);
}

void Trail::stopWorkout()
{
    qDebug("stop work out");
    setStarted(false);
}

