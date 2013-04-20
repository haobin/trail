/*
 * GpsLocation.cpp
 *
 *  Created on: Apr 19, 2013
 *      Author: hali
 */

#include "GpsLocation.hpp"
#include <QtLocationSubset/qgeopositioninfosource.h>
#include <QVariant>
#include <qobject.h>
#include <bb/cascades/maps/MapView>
#include <bb/platform/geo/GeoLocation>

using QtMobilitySubset::QGeoPositionInfoSource;
using bb::platform::geo::GeoLocation;

GpsLocation::GpsLocation(QObject *parent) :
    QObject(parent),
    mLocationPending(true),
    mGroundSpeed(0.0),
    mLatitude(43.468245),
    mLongitude(-80.519603),
    mDistance(0.0),
    mAvgSpeed(0.0),
    mPrevCoor(),
    mPrevPin(),
    mMapData(NULL),
    mStarttime(QDateTime::currentDateTime())
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
    setLatitude(latitude);
    setLongitude(longitude);
    updateDistance(pos.coordinate());
    qDebug("haobin latitude=%f, longitude=%f, groundSpeed=%f", latitude, longitude, groundSpeed);

    if (mMapData != NULL) {
        if ( (!mPrevPin.isValid()) || mPrevPin.distanceTo(pos.coordinate()) >= 20 ) {
            mPrevPin = pos.coordinate();
            GeoLocation *loc = new GeoLocation(latitude, longitude);
            mMapData->add(loc);
        }
    }
}

void GpsLocation::updateDistance(QtMobilitySubset::QGeoCoordinate coor)
{
    if (mPrevCoor.isValid()) {
        mDistance += coor.distanceTo(mPrevCoor);
        Q_EMIT distanceChanged();

        // update avg speed
        if (mDistance > 0.01) {
            double elapsedHours = mStarttime.secsTo(QDateTime::currentDateTime()) / 3600.0;
            mAvgSpeed = (mDistance / elapsedHours) / 1000;
            Q_EMIT avgSpeedChanged();
        }
    }
    mPrevCoor = coor;
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

double GpsLocation::getLatitude() const
{
    return mLatitude;
}

void GpsLocation::setLatitude(double lat)
{
    mLatitude = lat;
    Q_EMIT latitudeChanged();
}

double GpsLocation::getLongitude() const
{
    return mLongitude;
}

void GpsLocation::setLongitude(double lon)
{
    mLongitude = lon;
    Q_EMIT longitudeChanged();
}

Q_INVOKABLE void GpsLocation::mapviewCreated(QObject *mapobj)
{

    using namespace bb::cascades::maps;
    if (mapobj != NULL) {
        MapView *mapview = qobject_cast<MapView*>(mapobj);
        if (mapview) {
            MapData *mapData = mapview->mapData();
            if (mapData) {
                qDebug("haobin got mapdata!");
                mMapData = mapData;
            }
        }
    } else {
        qWarning("haobin mapview is null.");
    }
}

int GpsLocation::getDistance() const
{
    return static_cast<int>(mDistance);
}

QString GpsLocation::getAvgSpeed() const
{
    return QString::number(mAvgSpeed, 'f', 2);
}
