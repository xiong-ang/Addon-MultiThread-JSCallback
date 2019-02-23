const addon = require('./build/Release/callback');
//const addon = require('./build/Debug/callback');

/*
setTimeout(() => {
  addon((msg) => {
    console.log(msg);
  });
}, 10000);
*/

/*
addon.callback_uv_async((msg) => {
  console.log(msg);
});
*/

addon.callback_uv_queue_work((msg) => {
  console.log(msg);
});

console.log("Start running");