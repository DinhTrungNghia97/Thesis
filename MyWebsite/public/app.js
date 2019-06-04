/*
var humid0 = document.getElementById("humid0");
var humid1 = document.getElementById("humid1");
var temp0 = document.getElementById("temp0");
var temp1 = document.getElementById("temp1");
*/


var g1 = new JustGage({
		id: 'g1',
		value: 0,		
		min: 0,
		max: 100,
		valueFontFamily: "Roboto",
		title: "Temparature 0",
		titlePosition: "below",
		label: "°C",
		donut: true,
		pointer: true,
		gaugeWidthScale: 0.2,
		decimals: 2,
		pointerOptions: {
			toplength: 10,
			bottomlength: 10,
			bottomwidth: 8,
			color: '#000'
		},
		customSectors: [{
			color: "#ff0000",
			lo: 40,
			hi: 80
		}, {
			color: "#00ff00",
			lo: 0,
			hi: 40
			}],
		counter: true
		});

var g2 = new JustGage({
		id: 'g2',
		value: 0,		
		min: 0,
		max: 100,
		valueFontFamily: "Roboto",
		title: "Temparature 1",
		titlePosition: "below",
		label: "°C",
		donut: true,
		pointer: true,
		gaugeWidthScale: 0.2,
		decimals: 2,
		pointerOptions: {
			toplength: 10,
			bottomlength: 10,
			bottomwidth: 8,
			color: '#000'
		},
		customSectors: [{
			color: "#ff0000",
			lo: 40,
			hi: 80
		}, {
			color: "#00ff00",
			lo: 0,
			hi: 40
			}],
		counter: true
		});
var g3 = new JustGage({
		id: 'g3',
		value: 0,		
		min: 0,
		max: 100,
		valueFontFamily: "Roboto",
		title: "Temparature 2",
		titlePosition: "below",
		label: "°C",
		donut: true,
		pointer: true,
		gaugeWidthScale: 0.2,
		decimals: 2,
		pointerOptions: {
			toplength: 10,
			bottomlength: 10,
			bottomwidth: 8,
			color: '#000'
		},
		customSectors: [{
			color: "#ff0000",
			lo: 40,
			hi: 80
		}, {
			color: "#00ff00",
			lo: 0,
			hi: 40
			}],
		counter: true
		});
var g4 = new JustGage({
		id: 'g4',
		value: 0,		
		min: 0,
		max: 100,
		valueFontFamily: "Roboto",
		title: "Humidity 0",
		titlePosition: "below",
		label: "%",
		donut: true,
		pointer: true,
		gaugeWidthScale: 0.2,
		decimals: 2,
		pointerOptions: {
          toplength: 8,
          bottomlength: -20,
          bottomwidth: 6,
          color: '#000'
		},
		customSectors: [{
			color: "#ff0000",
			lo: 50,
			hi: 100
		}, {
			color: "#00ff00",
			lo: 0,
			hi: 50
			}],
		counter: true
		});
var g5 = new JustGage({
		id: 'g5',
		value: 0,		
		min: 0,
		max: 100,
		valueFontFamily: "Roboto",
		title: "Humidity 1",
		titlePosition: "below",
		label: "%",
		donut: true,
		pointer: true,
		gaugeWidthScale: 0.2,
		decimals: 2,
		pointerOptions: {
          toplength: 8,
          bottomlength: -20,
          bottomwidth: 6,
          color: '#000'
		},
		customSectors: [{
			color: "#ff0000",
			lo: 50,
			hi: 100
		}, {
			color: "#00ff00",
			lo: 0,
			hi: 50
			}],
		counter: true
		});	
var g6 = new JustGage({
		id: 'g6',
		value: 0,		
		min: 0,
		max: 100,
		valueFontFamily: "Roboto",
		title: "Humidity 2",
		titlePosition: "below",
		label: "%",
		donut: true,
		pointer: true,
		gaugeWidthScale: 0.2,
		decimals: 2,
		pointerOptions: {
          toplength: 8,
          bottomlength: -20,
          bottomwidth: 6,
          color: '#000'
		},
		customSectors: [{
			color: "#ff0000",
			lo: 50,
			hi: 100
		}, {
			color: "#00ff00",
			lo: 0,
			hi: 50
			}],
		counter: true
		});
	  
var read_humid_0 = firebase.database().ref().child("Humidity 0");  
read_humid_0.on('value', function(snapshot){
//humid0.innerHTML = snapshot.val();
var globalChartData = parseFloat(snapshot.val());
var Time = (new Date()).getTime();
var DataPoint = { x: Time, y: globalChartData };
chart0.series[0].addPoint(DataPoint, true);
g4.refresh(snapshot.val());
});
	
var read_humid_1 = firebase.database().ref().child("Humidity 1");  
read_humid_1.on('value', function(snapshot){
//humid1.innerHTML = snapshot.val();
g5.refresh(snapshot.val());
});

var read_humid_2 = firebase.database().ref().child("Humidity 2");  
read_humid_2.on('value', function(snapshot){
//humid1.innerHTML = snapshot.val();
g6.refresh(snapshot.val());
});
	
var read_temp_0 = firebase.database().ref().child("Temparature 0");  
read_temp_0.on('value', function(snapshot){
var globalChartData = parseFloat(snapshot.val());
var Time = (new Date()).getTime();
var DataPoint = { x: Time, y: globalChartData };
chart0.series[1].addPoint(DataPoint, true);
g1.refresh(snapshot.val());
});
	
var read_temp_1 = firebase.database().ref().child("Temparature 1");  
read_temp_1.on('value', function(snapshot){
//temp1.innerHTML = snapshot.val();
g2.refresh(snapshot.val());
});

var read_temp_2 = firebase.database().ref().child("Temparature 2");  
read_temp_2.on('value', function(snapshot){
//temp1.innerHTML = snapshot.val();
g3.refresh(snapshot.val());
});

var chart0;
        document.addEventListener('DOMContentLoaded', function() {
            chart0 = Highcharts.chart('g7', {
                chart: {
                    type: 'spline',
                },
				time: {
					useUTC: false
				},
                title: {
                    text: 'Live Measurement Data Collection'
                },
				tooltip: {
					headerFormat: '<b>{series.name}</b><br/>',
					pointFormat: '{point.x:%Y-%m-%d %H:%M:%S}<br/>{point.y:.2f}'
				},
				legend: {
					enabled: true,
				},
				exporting: {
					enabled: false
				},
                xAxis: {
                    type: 'datetime',
                    tickPixelInterval: 150,
                    maxZoom: 20 * 1000
                },
                yAxis: {
                    minPadding: 0.2,
                    maxPadding: 0.2,
                    title: {
                        text: 'Value',
                        margin: 80
                    }
                },

				series: [{
					name: 'Humidity 0',
					data: []
				},{
					name: 'Temparature 0',
					data: []
				}]
            });
        });	


function getDataCharts(){
	var read_humid_0 = firebase.database().ref().child("Humidity 0");
	read_humid_0.on('value', function(snapshot){
	//humid0.innerHTML = snapshot.val();
	globalChartData = parseFloat(snapshot.val());
	return globalChartData;
});}