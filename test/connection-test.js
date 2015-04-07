var net = require('net');

var client = new net.Socket();
client.connect(5293, '127.0.0.1', function() {
	console.log('Connected to server');
	console.log('Sending: Ping');
	client.write('Ping');
});

client.on('data', function(data) {
	console.log('Received: ' + data);
	client.destroy();
});

client.on('close', function() {
	console.log('Connection closed');
});
