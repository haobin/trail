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

using QtMobilitySubset::QGeoPositionInfo;

class GpsLocation: public QObject
{
Q_OBJECT


Q_PROPERTY(bool locationPending READ isLocationPending NOTIFY locationPendingChanged)


Q_SIGNALS:
void locationPendingChanged();

public:
    GpsLocation(QObject *parent = 0);
    virtual ~GpsLocation();

    bool isLocationPending() const;

public Q_SLOTS:
    void positionUpdateTimeout();
    void positionUpdated(const QGeoPositionInfo &pos);

private:

    void setLocationPending(bool pending);
    bool mLocationPending;
};

#endif /* GPSLOCATION_HPP_ */
