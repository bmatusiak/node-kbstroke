// Copyright 2013 Bradley Matusiak

var events = require('events');

var bindings = require('./build/Release/binding');

exports = module.exports = new events.EventEmitter();

var enabled = false;
var currentKeyMap = [];
var currentMousePos = [];

bindings.KeyMap(function(err,keymap,numLock,capsLock,scrollLock){
    currentKeyMap = keymap;
});

var checkKeyMap = function (app) {
    if(enabled){
        bindings.KeyMap(function(err,keymap,numLock,capsLock,scrollLock,mousePos){
            processKeyMap(keymap,numLock,capsLock,scrollLock,mousePos);
        });
        process.nextTick(checkKeyMap);
    }
};

function processKeyMap(keymap,numLock,capsLock,scrollLock,mousePos){
    for(var i = 0; i <= 256 ; i++){
        if(keymap[i] === 0 && currentKeyMap[i] === 1){
            exports.emit("keyup",i,numLock,capsLock,scrollLock,mousePos);
        }
        
        if(keymap[i] === 1 && currentKeyMap[i] === 0){
            exports.emit("keydown",i,numLock,capsLock,scrollLock,mousePos);
        }
        
        currentKeyMap[i] = keymap[i];
    }
    
    if(mousePos[0] !== currentMousePos[0] || mousePos[1] !== currentMousePos[1]){
        exports.emit("mousemove",{x:mousePos[0],y:mousePos[1]});
    }
    
    currentMousePos[0] = mousePos[0];
    currentMousePos[1] = mousePos[1];
}

exports.enable = function(){
    enabled = true;
    process.nextTick(checkKeyMap);
};
exports.disable = function(){
    enabled = false;
};
