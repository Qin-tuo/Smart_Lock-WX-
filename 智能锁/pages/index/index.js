var switch_value;
var connect_value;
var temp;
var hum;
var deviceConnected = false

const htmlid="https://api.heclouds.com/devices/";
const devid=932077948; 
const apikey='31z==n=mimRIFErDm=ESQeluvaU=';

const deviceInfoURL = "https://api.heclouds.com/devices/" + devid

const getDataStreamURL = "https://api.heclouds.com/devices/" + devid + "/datastreams";

const urltest1 = getDataStreamURL + "/key" ;//'http://api.heclouds.com/devices/520332079/datastreams/dht11_humi';  //开关取流URL
// const urlvtest = getDataStreamURL + "/Vrms";//电压取流
// const urlitest = getDataStreamURL + "/Irms";//电流取流
// const urlWtest = getDataStreamURL + "/W_KWH";//用电量取流
// const urlPAtest = getDataStreamURL + "/PAct";//功率取流
// const urlSBtest = getDataStreamURL + "/shebei";//功率取流

const controlURL = "http://api.heclouds.com/cmds?device_id="+devid


// function getTemp_Test() {
//   wx.request({
//     url: urlitest, // 仅为示例，并非真实的接口地址 
//     method: 'GET',
//     header: {
//       // 'content-type': 'application/json' // 默认值
//       'api-key': apikey//已经修改
//     },
//     success(res) {
//       temp = res.data.data.current_value;
//       //console.log(res.data.data.current_value)
//     }
//   })
// }

// function getHum_Test() {
//   wx.request({
//     url: urlvtest, // 仅为示例，并非真实的接口地址 
//     method: 'GET',
//     header: {
//       // 'content-type': 'application/json' // 默认值
//       'api-key': apikey
//     },
//     success(res) {
//       //console.log(res.data.data.current_value)
//     }
//   })
// }

function getKey_Test() {
  wx.request({
    url: urltest1, // 仅为示例，并非真实的接口地址 
    method: 'GET',
    header: {
      // 'content-type': 'application/json' // 默认值
      'api-key': apikey//已经修改
    },
    success(res) {
      temp = res.data.data.current_value;
      console.log(res.data.data.current_value)
    }
  })
}

// function getW_Test() {
//   wx.request({
//     url: urlWtest, // 仅为示例，并非真实的接口地址 
//     method: 'GET',
//     header: {
//       // 'content-type': 'application/json' // 默认值
//       'api-key': apikey//已经修改
//     },
//     success(res) {
//       temp = res.data.data.current_value;
//       console.log(res.data.data.current_value)
//     }
//   })
// }

// function getPA_Test() {
//   wx.request({
//     url: urlPAtest, // 仅为示例，并非真实的接口地址 
//     method: 'GET',
//     header: {
//       // 'content-type': 'application/json' // 默认值
//       'api-key': apikey//已经修改
//     },
//     success(res) {
//       temp = res.data.data.current_value;
//       console.log(res.data.data.current_value)
//     }
//   })
// }

// function getSB_Test() {
//   wx.request({
//     url: urlSBtest, // 仅为示例，并非真实的接口地址 
//     method: 'GET',
//     header: {
//       // 'content-type': 'application/json' // 默认值
//       'api-key': apikey//已经修改
//     },
//     success(res) {
//       temp = res.data.data.current_value;
//       console.log(res.data.data.current_value)
//     }
//   })
// }

function Ledtest(value) {
  wx.request({
    url: controlURL, // 仅为示例，并非真实的接口地址 
    method: 'POST',
    data: "{redled}" + value,
    header: {
      // 'content-type': 'application/json' // 默认值
      'api-key': apikey
    },
    success(res) {
      if(value==1){
        console.log("开灯指令发送成功")
      }else{
        console.log("关灯指令发送成功")
      }
    }
  })
}
Page({
  data: {
    message: "设备还未连接",
  },
  onLoad: function () {
    this.connect();
    let timer = setInterval(() => {
      this.connect();
    }, 3000)
  },
  switch1Change(e) {
    var switch_value = e.detail.value ;
    if (switch_value == true) {
      //Ledtest("1");
      controlLED('key', 'open')
    }
    else if (switch_value == false) {
      // Ledtest("0");
      controlLED('key', 'close')
    }
  },
  // getTemp_Test() {
  //   return new Promise(resolve => {
  //     wx.request({
  //       url: urlitest, // 仅为示例，并非真实的接口地址 
  //       method: 'GET',
  //       header: {
  //         // 'content-type': 'application/json' // 默认值
  //         'api-key': apikey
  //       },
  //       success: resolve
  //     })
  //   })
  // },
  // getHum_Test() {
  //   return new Promise(resolve => {
  //     wx.request({
  //       url: urlvtest, // 仅为示例，并非真实的接口地址   
  //       method: 'GET',
  //       header: {
  //         // 'content-type': 'application/json' // 默认值
  //         'api-key': apikey
  //       },
  //       success: resolve
  //     })
  //   })
  // },
  getKey_Test(){
    return new Promise(resolve => {
      wx.request({
        url: urltest1, // 仅为示例，并非真实的接口地址 
        method: 'GET',
        header: {
          // 'content-type': 'application/json' // 默认值
          'api-key': apikey
        },
        success: resolve
      })
    })
  },
  // getYD_Test(){
  //   return new Promise(resolve => {
  //     wx.request({
  //       url: urlWtest, // 仅为示例，并非真实的接口地址 
  //       method: 'GET',
  //       header: {
  //         // 'content-type': 'application/json' // 默认值
  //         'api-key': apikey
  //       },
  //       success: resolve
  //     })
  //   })
  // },
  // getPA_Test(){
  //   return new Promise(resolve => {
  //     wx.request({
  //       url: urlPAtest, // 仅为示例，并非真实的接口地址 
  //       method: 'GET',
  //       header: {
  //         // 'content-type': 'application/json' // 默认值
  //         'api-key': apikey
  //       },
  //       success: resolve
  //     })
  //   })
  // },
  connect() {
    new Promise(resolve => {
      wx.request({
        url: deviceInfoURL, // 仅为示例，并非真实的接口地址 
        method: 'GET',
        header: {
          // 'content-type': 'application/json' // 默认值
          'api-key': apikey
        },
        success: resolve
      })
    })
      .then(res => {
        connect_value = res.data.data.online;
        if (connect_value == true) {
          console.log("设备已经连接");
          deviceConnected=true
          
          //deviceConnected = true  
          // this.getHum_Test()
          //   .then(res => {
          //     let hum = res.data.data.current_value;
          //     this.setData({ dianya: hum });
          //   })
          // this.getTemp_Test()
          //   .then(res => {
          //     let temp = res.data.data.current_value;
          //     this.setData({ dianliu: temp });
          //   })
          // this.getYD_Test()
          //   .then(res => {
          //     let temp = res.data.data.current_value;
          //     this.setData({ yongdianliang: temp });
          //   })
          // this.getPA_Test()
          //   .then(res => {
          //     let temp = res.data.data.current_value;
          //     this.setData({ gonglv: temp });
          //   })
          this.getKey_Test()
            .then(res => {
              let temp = res.data.data.current_value;
              //this.setData({ dianliu: temp });
              if(temp== 1) {
                this.setData({ yellow_checked : true})
              } else {
                this.setData({ yellow_checked : false})
              }
            })
          this.setData({ message: "设备已经连接" });
        } else if (connect_value == false) {
          //console.log("设备还未连接");
          this.setData({ message: "设备还未连接" })
        }
      })
  }
})

function controlLED(hardware_id ,switch_value) {
  // console.log("发送命令：" + hardware_id + ":{" + switch_value + "}")
  console.log("发送命令：" + hardware_id + ":" +switch_value )
  //按钮发送命令控制硬件
  wx.request({
    url: controlURL ,//sendCommandURL + "?device_id=" + deviceid,
    method: 'POST',
    header: {
      'content-type': 'application/x-www-form-urlencoded',
      "api-key": apikey
    },
    // data: hardware_id + ":{" + switch_value + "}",      //TODO 设计自定义语言 blueled:{V}, 预感这边可能会有问题
    data: hardware_id + ":" + switch_value ,
    success(res) {
      console.log("控制成功")
      console.log(res)
    }
  })
}



