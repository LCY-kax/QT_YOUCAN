import QtQuick 2.5
import QtGraphicalEffects 1.0
//import QtQuick.Layouts 1.5
import QtQuick.Controls 1.0


Item {
    id: root

    property int fuel:0

    Timer {
        id: timer
        interval: 300 // 每秒更新一次
        running: true
        repeat: true
        onTriggered: {
            progressBar.value += 1;
            if (progressBar.value >= progressBar.maximumValue) {
                progressBar.value = progressBar.minimumValue;
            }
            fuel+=1;
            if (fuel > 100) {
                fuel = 0;
            }
        }
    }
    onFuelChanged: {
        canvas.requestPaint();
    }

    ProgressBar{
        id:progressBar
        anchors.top: fule.bottom
        anchors.topMargin: 20
        width: 160
        value: 0 // 进度值，范围是 0 到 100
        maximumValue: 100 // 最大值
        minimumValue: 0 // 最小值
    }

    Item{
        id: fule
        y:30
        width: 190
        height: 8

        Canvas {
            id: canvas
            anchors.fill: parent
//            visible: false
            onPaint: {
                var width=0
                var ctx = canvas.getContext("2d");
                ctx.reset();
                if(fuel>=0&&fuel<=100){
                    width=fuel*1.78
                }
                if(width<=24){
                    ctx.beginPath();
                    ctx.moveTo(0,parent.height);
                    ctx.lineTo(parent.height,0);
                    if(width>0){
                        ctx.stroke();
                    }
                    ctx.lineTo(parent.height+width,0);
                    ctx.lineTo(width,parent.height);
                    if(width>0){
                        ctx.stroke();
                    }
                    ctx.closePath();
                    ctx.fillStyle="#FE4F4F"
                    ctx.fill();

                }else{
                    ctx.beginPath();
                    ctx.moveTo(0,parent.height);
                    ctx.lineTo(parent.height,0);
                    ctx.stroke();
                    ctx.lineTo(parent.height+width,0);
                    ctx.lineTo(width,parent.height);
                    ctx.stroke();
                    ctx.closePath();
                    var grd=ctx.createLinearGradient(0,0,width,0);
                    grd.addColorStop(0,"#5BA5C7");
                    grd.addColorStop(1,"#F4FCFF");
                    ctx.fillStyle=grd
                    ctx.fill();
                    //                ctx.stroke();

                    //高光
                    var g=ctx.createLinearGradient(1,0,0,3);
                    g.addColorStop(0,Qt.rgba(255/255,255/255,255/255,0.3));
                    g.addColorStop(1,Qt.rgba(255/255,255/255,255/255,0));
                    ctx.fillStyle=g
                    ctx.fillRect(8, 0, width-1, 3);

                }
                //边框
                ctx.beginPath();
                //                ctx.moveTo(parent.height,0);
                //                ctx.lineTo(0,parent.height);
                ctx.moveTo(0,parent.height);
                ctx.lineTo(width, parent.height);
                ctx.closePath();
                ctx.lineWidth = 1;
                ctx.strokeStyle = '#87FEFF';
                ctx.stroke();
            }

            onPainted: {
//                if(firstStart){
//                    opacityMask.visible = true
//                    //                    speedNumberAnimator.running = true
//                    firstStart = false
//                }

            }
        }

    }



}
