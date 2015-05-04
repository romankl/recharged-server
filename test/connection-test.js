const net = require('net');
const client = new net.Socket();
const assert = require('assert')

describe('Connection test:', function(){
  describe('STATUS', function(){
    it('should return OK when STATUS is used', function(done){

		client.connect(5293, '127.0.0.1', function() {
			console.log('Connected to server');
			console.log('Sending: STATUS');
			client.write('STATUS\r\n');
		});

		client.on('data', function(data) {
			console.log('Received: ' + data);
			assert(data == 'OK')
			client.destroy();
		});

		client.on('close', function() {
			console.log('Connection closed');
			done();
		});
    })
  })
})
