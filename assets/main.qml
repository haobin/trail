// Navigation pane project template
import bb.cascades 1.0
import bb.cascades.maps 1.0

NavigationPane {
    id: navigationPane
    Page {
        // page with a picture thumbnail
        Container {
            background: Color.White
            layout: DockLayout {
            }
            
            Shade {
                id: shade
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                visible: GpsLocation.locationPending
//                visible: false
            }
            

            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                visible: ! shade.visible
                layout: DockLayout {}
                
                MapView {
                    id: mapview
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Center
                    latitude: GpsLocation.latitude
                    longitude: GpsLocation.longitude
                    altitude: 1000

                    onCreationCompleted: {
                        GpsLocation.mapviewCreated(mapview);
                    }
                }

                Container {
                    id: infoPanel
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Bottom
                    leftPadding: 20
                    bottomPadding: 15
                    Label {
                        text: qsTr("Average Speed: %1 km/h.  Distance: %2 m").arg(GpsLocation.avgSpeed).arg(GpsLocation.distance)
                        textStyle.color: Color.create("#e05d1b")
                        textStyle.fontSize: FontSize.Medium
                    }
                }
            }

        }
    }
    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("NavigationPane - onCreationCompleted()");

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
}
