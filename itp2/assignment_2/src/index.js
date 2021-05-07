const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);
const spawn = require('child_process').spawn;

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', (socket) => {
  console.log('a user connected');

  let gameProcess = spawn('./game');
    gameProcess.stdout.setEncoding('utf-8');
    gameProcess.stdout.on('data', (data) => {
        socket.emit('newLine', data);
    })
});

server.listen(80, () => {
  console.log('listening on *:80');
});