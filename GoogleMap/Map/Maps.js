/* // Add map
    function myMap() {
        // Add marker
        var marker = new google.maps.Marker({
            position: new google.maps.LatLng(secObject.latPosition, 80.33),
            map: map,
            title: "Marker A",
        });

        google.maps.event.addListener(marker, 'click', function(){
            // this will translate marker in center of Map
            map.panTo(marker.getPosition());
        });

        // Add event listener
        google.maps.event.addListener(map, 'zoom_changed', function(){
            //alert(map.getZoom());
        });

        // Add polyline
        var points = [ new google.maps.LatLng(12.57, 77.37), new google.maps.LatLng(14.57, 77.37), new google.maps.LatLng(14.57, 73.37) ];
        var polyOptions = {
            path: points,
            strokeColor: '#FF0000',
            strokeOpacity: 1.0,
            strokeWeight: 2
        };

        historyPolyline = new google.maps.Polyline(polyOptions);
        historyPolyline.setMap(map);

        // Add polygon
        var nPoints = [ new google.maps.LatLng(12.314166, 75.432),new google.maps.LatLng(15.2653, 70.4325), new google.maps.LatLng(8.8288, 76.5483) ];
        var polygon = new google.maps.Polygon(
        {
            paths: nPoints,
            fillColor:  '#000000',
            fillOpacity: 0.2,
            strokeWeight: 3,
            strokeColor: '#fff000',
        });

        polygon.setMap(map);
        google.maps.event.addDomListener(window, 'load', initialize);
    }
*/

var Map;

var Marker;

function updateMarker(lat){
    var latLng = new google.maps.LatLng(lat, 77.59);
    Marker.setPosition(latLng);
}

function initialize(){

    var mapOptions = {
        center: new google.maps.LatLng(20, 77),
        zoom: 10,
        mapTypeId: google.maps.MapTypeId.HYBRID
    }

    Map = new google.maps.Map(document.getElementById("map-canvas"), mapOptions);

    Marker = new google.maps.Marker({
                                        position: new google.maps.LatLng(dataManager.lattitute, dataManager.longitute),
                                        map: Map,
                                        title: "Marker A",
                                    });
}

function loadScript() {
    var script = document.createElement("script");
    script.type = "text/javascript";
    script.src = "http://maps.google.com/maps/api/js?key="+ApiKey+"&callback=initialize";
    document.body.appendChild(script);
}

window.onload = loadScript;
