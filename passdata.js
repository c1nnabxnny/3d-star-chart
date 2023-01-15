/*
This code is the javascript side of a two-part script that allows data to be passed between python and js scripts.
I copied this code from the following YouTube video: https://www.youtube.com/watch?v=lSAFVMaaH-w.
Check out that link if you want to understand how this code works.
Made by Apes in Capes
*/

const spawner = require('child_process').spawn;

// object
const dataToPassIn = {
    dataSent: 'send this to python script',
    dataReturned: undefined
};

console.log('data sent to python script: ', dataToPassIn);

const pythonProcess = spawner('python', ['./python.py', JSON.stringify(dataToPassIn)]);

pythonProcess.stdout.on('data', (data) => {
    console.log('data received from python script', JSON.parse(data.toString()));
});