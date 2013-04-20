/*
 * GpsLocation.hpp
 *
 *  Created on: Apr 19, 2013
 *      Author: hali
 */

#ifndef GPSLOCATION_HPP_
#define GPSLOCATION_HPP_

#include <qobject.h>
#include <QtLocationSubset/qgeopositioninfosource.h>
#include <bb/cascades/maps/MapData>

using QtMobilitySubset::QGeoPositionInfo;

class GpsLocation: public QObject
{
Q_OBJECT


Q_PROPERTY(bool locationPending READ isLocationPending NOTIFY locationPendingChanged)
Q_PROPERTY(double groundSpeed READ getGroundSpeed NOTIFY groundSpeedChanged)
Q_PROPERTY(double latitude READ getLatitude NOTIFY latitudeChanged)
Q_PROPERTY(double longitude READ getLongitude NOTIFY longitudeChanged)


Q_SIGNALS:
void locationPendingChanged();
void groundSpeedChanged();
void latitudeChanged();
void longitudeChanged();

public:
    GpsLocation(QObject *parent = 0);
    virtual ~GpsLocation();

    bool isLocationPending() const;

    double getGroundSpeed() const;

    void setGroundSpeed(double speed);

    double getLatitude() const;

    void setLatitude(double lat);

    double getLongitude() const;

    void setLongitude(double lon);

public Q_SLOTS:
    void positionUpdateTimeout();
    void positionUpdated(const QGeoPositionInfo &pos);
    Q_INVOKABLE void mapviewCreated(QObject *mapview);
private:

    void setLocationPending(bool pending);
    bool mLocationPending;
    double mGroundSpeed;
    double mLatitude;
    double mLongitude;
    bb::cascades::maps::MapData *mMapData;
};

#endif /* GPSLOCATION_HPP_ */
