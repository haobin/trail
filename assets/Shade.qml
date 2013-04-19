import bb.cascades 1.0

Container {
    id: shade
    background: Color.Black
    opacity: 0.8
    
    layout: DockLayout {
    }

    Container {
        id: activityIndicator
        horizontalAlignment: HorizontalAlignment.Center
        verticalAlignment: VerticalAlignment.Center

        Label {
            text: "Waiting for GPS Signal..."
        }
    }
}