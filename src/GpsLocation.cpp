/*
 * GpsLocation.cpp
 *
 *  Created on: Apr 19, 2013
 *      Author: hali
 */

#include "GpsLocation.hpp"
#include <QtLocationSubset/qgeopositioninfosource.h>
#include <QVariant>

using QtMobilitySubset::QGeoPositionInfoSource;

GpsLocation::GpsLocation(QObject *parent) :
    QObject(parent),
    mLocationPending(true),
    mGroundSpeed(0.0)
{
    // TODO Auto-generated constructor stub
    QGeoPositionInfoSource *src = QGeoPositionInfoSource::createDefaultSource(this);
    src->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
    src->setUpdateInterval(10 * 1000);
    src->setProperty("canRunInBackground", QVariant(true));

    bool updateTimeoutConnected = connect(src, SIGNAL(updateTimeout()), this,
        SLOT(positionUpdateTimeout()));

    if (!updateTimeoutConnected) {
       qWarning("haobin failed to connect to positionUpdateTimeout()");
    }

    // Connect the positionUpdated() signal to a
    // slot that handles position updates.

    bool positionUpdatedConnected = connect(src, SIGNAL(positionUpdated(const QGeoPositionInfo &)),
        this, SLOT(positionUpdated(const QGeoPositionInfo &)));

    if (positionUpdatedConnected) {
        // Signal and slot connected.

        // Start receiving updates to the position of the device.
        src->startUpdates();
    } else {
        qWarning("haobin failed to connect to positionUpdateTimeout()");
    }
}

GpsLocation::~GpsLocation()
{
    // TODO Auto-generated destructor stub
}



void GpsLocation::positionUpdateTimeout()
{
    qWarning("haobin positionUpdateTimeout");
    setLocationPending(true);
}


void GpsLocation::positionUpdated(const QGeoPositionInfo &pos)
{
    setLocationPending(false);
    double latitude = pos.coordinate().latitude();
    double longitude = pos.coordinate().longitude();
    qreal groundSpeed = pos.attribute(QGeoPositionInfo::GroundSpeed);
    setGroundSpeed(groundSpeed);
    qDebug("haobin latitude=%f, longitude=%f, groundSpeed=%f", latitude, longitude, groundSpeed);
}

void GpsLocation::setLocationPending(bool pending)
{
    if (pending != mLocationPending) {
        mLocationPending = pending;
        Q_EMIT locationPendingChanged();
    }
}

bool GpsLocation::isLocationPending() const
{
    return mLocationPending;
}


double GpsLocation::getGroundSpeed() const
{
    return mGroundSpeed;
}

void GpsLocation::setGroundSpeed(double speed)
{
    mGroundSpeed = speed;
    Q_EMIT groundSpeedChanged();
}
