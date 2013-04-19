// Navigation pane project template
#ifndef Trail_HPP_
#define Trail_HPP_

#include <QObject>

#include <bb/cascades/QmlDocument>
#include "GpsLocation.hpp"

namespace bb
{
namespace cascades
{
class Application;
}
}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class Trail: public QObject
{
Q_OBJECT

    /**
     * work out started or not
     */
Q_PROPERTY(bool started READ isStarted NOTIFY startedChanged)

public:
    Trail(bb::cascades::Application *app);
    virtual ~Trail()
    {
    }

    /**
     * @return True if work out is started.
     */
    bool isStarted() const;


    /**
     * Starts the workout.
     *
     */
    Q_INVOKABLE void startWorkout();

    Q_INVOKABLE void stopWorkout();

Q_SIGNALS:
    void startedChanged();


private:
    void registerContext(bb::cascades::QmlDocument *qml);

    void setStarted(bool started);

    bool mStarted;
    GpsLocation mGpsLocation;
};

#endif /* Trail_HPP_ */
