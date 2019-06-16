/*
var humid0 = document.getElementById("humid0");
var humid1 = document.getElementById("humid1");
var temp0 = document.getElementById("temp0");
var temp1 = document.getElementById("temp1");
*/
var con_status = firebase.database().ref().child("Alert");
	con_status.on('value', function(snapshot){
	if (snapshot.val() == "0") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Good";
		status3.innerHTML = "Good";
		status4.innerHTML = "Good";
		status5.innerHTML = "Good";
	}
	else if (snapshot.val() == "1") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Good";
		status3.innerHTML = "Failed";
		status4.innerHTML = "Failed";
		status5.innerHTML = "Failed";
	}
	else if (snapshot.val() == "2") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Good";
		status3.innerHTML = "Failed";
		status4.innerHTML = "Good";
		status5.innerHTML = "Good";
	}
	else if (snapshot.val() == "3") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Good";
		status3.innerHTML = "Good";
		status4.innerHTML = "Failed";
		status5.innerHTML = "Good";
	}
	else if (snapshot.val() == "4") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Good";
		status3.innerHTML = "Good";
		status4.innerHTML = "Good";
		status5.innerHTML = "Failed";
	}
	else if (snapshot.val() == "5") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Good";
		status3.innerHTML = "Failed";
		status4.innerHTML = "Failed";
		status5.innerHTML = "Good";
	}
	else if (snapshot.val() == "6") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Good";
		status3.innerHTML = "Good";
		status4.innerHTML = "Failed";
		status5.innerHTML = "Failed";
	}
	else if (snapshot.val() == "7") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Good";
		status3.innerHTML = "Failed";
		status4.innerHTML = "Good";
		status5.innerHTML = "Failed";
	}
	else if (snapshot.val() == "8") {
		status1.innerHTML = "Failed";
		status2.innerHTML = "Failed";
		status3.innerHTML = "Unknown";
		status4.innerHTML = "Unknown";
		status5.innerHTML = "Unknown";
	}
	else if (snapshot.val() == "9") {
		status1.innerHTML = "Failed";
		status2.innerHTML = "Good";
		status3.innerHTML = "Unknown";
		status4.innerHTML = "Unknown";
		status5.innerHTML = "Good";
	}
	else if (snapshot.val() == "10") {
		status1.innerHTML = "Good";
		status2.innerHTML = "Failed";
		status3.innerHTML = "Good";
		status4.innerHTML = "Good";
		status5.innerHTML = "Unknown";
	}
});

var sen_status = firebase.database().ref().child("Sensor");
	sen_status.on('value', function(snapshot){
	if (snapshot.val() == "0") {
		status6.innerHTML = "Good";
		status7.innerHTML = "Good";
		status8.innerHTML = "Good";
	}
	else if (snapshot.val() == "1") {
		status6.innerHTML = "Failed";
		status7.innerHTML = "Failed";
		status8.innerHTML = "Failed";
	}
	else if (snapshot.val() == "2") {
		status6.innerHTML = "Failed";
		status7.innerHTML = "Good";
		status8.innerHTML = "Good";
	}
	else if (snapshot.val() == "3") {
		status6.innerHTML = "Good";
		status7.innerHTML = "Failed";
		status8.innerHTML = "Good";
	}
	else if (snapshot.val() == "4") {
		status6.innerHTML = "Good";
		status7.innerHTML = "Good";
		status8.innerHTML = "Failed";
	}
	else if (snapshot.val() == "5") {
		status6.innerHTML = "Failed";
		status7.innerHTML = "Failed";
		status8.innerHTML = "Good";
	}
	else if (snapshot.val() == "6") {
		status6.innerHTML = "Good";
		status7.innerHTML = "Failed";
		status8.innerHTML = "Failed";
	}
	else if (snapshot.val() == "7") {
		status6.innerHTML = "Failed";
		status7.innerHTML = "Good";
		status8.innerHTML = "Failed";
	}
});

var g1 = new JustGage({
		id: 'g1',
		value: 0,		
		min: 0,
		max: 100,
		valueFontFamily: "Roboto",
		title: "Temperature 1",
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
		title: "Temperature 2",
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
		title: "Temperature 3",
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
var g5 = new JustGage({
		id: 'g5',
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
var g6 = new JustGage({
		id: 'g6',
		value: 0,		
		min: 0,
		max: 100,
		valueFontFamily: "Roboto",
		title: "Humidity 3",
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
		
var Update = firebase.database().ref().child("Count");
Update.on('value', function(snapshot){
UpdateData();
}); 
	  
function UpdateData() {
	var Time = (new Date()).getTime();
	
	var read_humid_0 = firebase.database().ref().child("Humidity/0");
	read_humid_0.once('value', function(snapshot){
	var globalChartData = parseFloat(snapshot.val());
	var DataPoint = { x: Time, y: globalChartData };
	chart0.series[0].addPoint(DataPoint, true);
	g4.refresh(snapshot.val());
	});
		
	var read_humid_1 = firebase.database().ref().child("Humidity/1");  
	read_humid_1.once('value', function(snapshot){
	var globalChartData = parseFloat(snapshot.val());
	var DataPoint = { x: Time, y: globalChartData };
	chart1.series[0].addPoint(DataPoint, true);
	g5.refresh(snapshot.val());
	});

	var read_humid_2 = firebase.database().ref().child("Humidity/2");  
	read_humid_2.once('value', function(snapshot){
	var globalChartData = parseFloat(snapshot.val());
	var DataPoint = { x: Time, y: globalChartData };
	chart2.series[0].addPoint(DataPoint, true);
	g6.refresh(snapshot.val());
	});
	
	var read_temp_0 = firebase.database().ref().child("Temperature/0");  
	read_temp_0.once('value', function(snapshot){
	var globalChartData = parseFloat(snapshot.val());
	var DataPoint = { x: Time, y: globalChartData };
	chart0.series[1].addPoint(DataPoint, true);
	g1.refresh(snapshot.val());
	});
	
	var read_temp_1 = firebase.database().ref().child("Temperature/1");  
	read_temp_1.once('value', function(snapshot){
	var globalChartData = parseFloat(snapshot.val());
	var DataPoint = { x: Time, y: globalChartData };
	chart1.series[1].addPoint(DataPoint, true);
	g2.refresh(snapshot.val());
	});

	var read_temp_2 = firebase.database().ref().child("Temperature/2");  
	read_temp_2.once('value', function(snapshot){
	var globalChartData = parseFloat(snapshot.val());
	var DataPoint = { x: Time, y: globalChartData };
	chart2.series[1].addPoint(DataPoint, true);
	g3.refresh(snapshot.val());
	});
}
	
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
					name: 'Humidity 1 (%)',
					data: []
				},{
					name: 'Temperature 1 (°C)',
					data: []
				}]
            });
        });

var chart1;
        document.addEventListener('DOMContentLoaded', function() {
            chart1 = Highcharts.chart('g8', {
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
					name: 'Humidity 2 (%)',
					data: []
				},{
					name: 'Temperature 2 (°C)',
					data: []
				}]
            });
        });

var chart2;
        document.addEventListener('DOMContentLoaded', function() {
            chart2 = Highcharts.chart('g9', {
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
					name: 'Humidity 3 (%)',
					data: []
				},{
					name: 'Temperature 3 (°C)',
					data: []
				}]
            });
        });
var buttonstate=0;
function openForm() {
	buttonstate= 1 - buttonstate;
	if(buttonstate) {
		document.getElementById("myForm").style.display = "block";
		document.getElementById("view-status").innerHTML = "Close";
	}
	else {
		document.getElementById("myForm").style.display = "none";
		document.getElementById("view-status").innerHTML = "View Status";
	}
}