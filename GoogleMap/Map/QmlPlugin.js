var dataManager;
var qmlObject;
var ApiKey = "AIzaSyBCdNVOM-Zie0oZjy4Dg-4ImIXFAHvfNx0";

var webChannel = new QWebChannel(qt.webChannelTransport, function(channel) {
    // all published objects are available in channel.objects under
    // the identifier set in their attached WebChannel.id property
    dataManager = channel.objects.dataManager;
    qmlObject   = channel.objects.qmlObject;

    dataManager.getAPIKey(function(ret) {
        ApiKey = ret;

    });

    // connect to a signal
    qmlObject.someSignal.connect(function(message) {
        alert("Got signal: " + message);
    });

    // invoke a method, and receive the return value asynchronously
    qmlObject.someMethod("bar", function(ret) {
        alert("Got return value: " + ret);
    });
});
