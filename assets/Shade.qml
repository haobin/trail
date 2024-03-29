import bb.cascades 1.0

Container {
    id: shade
    background: Color.Black
    opacity: 0.5
    
    layout: DockLayout {
    }

    Container {
        id: activityIndicator
        horizontalAlignment: HorizontalAlignment.Center
        verticalAlignment: VerticalAlignment.Center

        Label {
            horizontalAlignment: HorizontalAlignment.Fill
            text: qsTr("Locating GPS Signal")
            textStyle.fontSize: FontSize.XLarge
            textStyle.textAlign: TextAlign.Center
            textStyle.color: Color.create("#fafafa")
        }

        Label {
            horizontalAlignment: HorizontalAlignment.Fill
            text: qsTr("This may take a few minutes...")
            textStyle.fontSize: FontSize.Small
            textStyle.textAlign: TextAlign.Center
            textStyle.fontStyle: FontStyle.Italic
            textStyle.color: Color.create("#fafafa")
        }

        ActivityIndicator {
            id: myIndicator
            running: true
            preferredWidth: 100
            topMargin: 80
            horizontalAlignment: HorizontalAlignment.Center
        }
    }
}