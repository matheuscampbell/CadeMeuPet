var geocoder;
var map;
var marker = false;

function initializeMap(lat = "-13.6398594", long = "-54.4660593") {
    var latlng = new google.maps.LatLng(lat, long);
    var mapOptions = {
        zoom: 3,
        center: latlng,
        mapTypeId: google.maps.MapTypeId.HYBRID,
    };
    map = new google.maps.Map(document.getElementById('map'), mapOptions);
}

$(".endMap").on("focusout", function (e) {
    codeAddress();
});

function setLocation(lat, long) {
    lat = parseFloat(lat);
    long = parseFloat(long);
    var latLong = new google.maps.LatLng(lat, long);
    map.setCenter(latLong);
    map.setZoom(18);
    if (!marker) {
        marker = new google.maps.Marker({
            map: map,
            position: latLong,
            draggable: true,
        });
    } else {
        marker.setPosition(latLong);
    }

}

function startRequests() {
    $.ajax({
        url: '/api/getActualLocation',
        method: 'get',
        dataType: 'json',
        success: function (data) {
            setLocation(data.lat, data.long);
            setTimeout(function () {
                startRequests();
            }, 1000);
        },
        error: function () {
            alert("ooops!, Ocorreu um erro.");
        }
    })
}

setTimeout(function () {
    startRequests();
}, 1000);