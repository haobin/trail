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
#include <QtLocationSubset/QGeoCoordinate>
#include <bb/system/SystemUiResult>

using QtMobilitySubset::QGeoPositionInfo;

class GpsLocation: public QObject
{
Q_OBJECT


Q_PROPERTY(bool locationPending READ isLocationPending NOTIFY locationPendingChanged)
Q_PROPERTY(double groundSpeed READ getGroundSpeed NOTIFY groundSpeedChanged)
Q_PROPERTY(QString avgSpeed READ getAvgSpeed NOTIFY avgSpeedChanged)
Q_PROPERTY(double latitude READ getLatitude NOTIFY latitudeChanged)
Q_PROPERTY(double longitude READ getLongitude NOTIFY longitudeChanged)
Q_PROPERTY(int distance READ getDistance NOTIFY distanceChanged)


Q_SIGNALS:
void locationPendingChanged();
void groundSpeedChanged();
void latitudeChanged();
void longitudeChanged();
void distanceChanged();
void avgSpeedChanged();

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

    int getDistance() const;

    QString getAvgSpeed() const;

public Q_SLOTS:
    void positionUpdateTimeout();
    void positionUpdated(const QGeoPositionInfo &pos);
    Q_INVOKABLE void mapviewCreated(QObject *mapview);
    void onDialogFinished(bb::system::SystemUiResult::Type);
private:

    void setLocationPending(bool pending);

    void updateDistance(QtMobilitySubset::QGeoCoordinate coor);

    void invokeLocationSettings() const;

    void promptToTurnOnLocation() const;

    bool mLocationPending;
    double mGroundSpeed;
    double mLatitude;
    double mLongitude;
    double mDistance;
    double mAvgSpeed;
    QtMobilitySubset::QGeoCoordinate mPrevCoor;
    QtMobilitySubset::QGeoCoordinate mPrevPin;
    bb::cascades::maps::MapData *mMapData;
    QDateTime mStarttime;
};

#endif /* GPSLOCATION_HPP_ */
