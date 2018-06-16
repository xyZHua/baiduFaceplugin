var exec = require('cordova/exec');

// var Baiduface = {
//     getFaceImage: function() {
//         exec(null, null, "Baiduface", "getFaceImage", []);
//     }
// };

// module.exports = Baiduface;


exports.getFaceImage = function (success, error) {
    exec(success, error,'Baiduface', 'getFaceImage',[])   
   };