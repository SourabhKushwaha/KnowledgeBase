var dataManager;
var qmlObject;

var webChannel = new QWebChannel(qt.webChannelTransport, function(channel) {
    // all published objects are available in channel.objects under
    // the identifier set in their attached WebChannel.id property
    dataManager = channel.objects.dataManager;
    qmlObject   = channel.objects.qmlObject
    /*secObject = channel.objects.secondObj;

    // connect to a signal
    myObject.someSignal.connect(function(message) {
        alert("Got signal: " + message);
    });

    // invoke a method, and receive the return value asynchronously
    myObject.someMethod("bar", function(ret) {
        alert("Got return value: " + ret);
    });*/
});
