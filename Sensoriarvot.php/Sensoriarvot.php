<!DOCTYPE html>
<html>
<head>
<body background="https://images.freecreatives.com/wp-content/uploads/2016/03/White-Snow-Background.jpg">
<title>IoT-Kukkaruukku</title>  
           <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>  
           <script type="text/javascript">  
           google.charts.load('current', {'packages':['corechart']}); 
           google.charts.setOnLoadCallback(LampoChart);
           google.charts.setOnLoadCallback(ValoChart);   
           google.charts.setOnLoadCallback(KosteusChart); 
           
           function LampoChart()  
           {  
                var data = google.visualization.arrayToDataTable([  
                          ['Lampo', ''],  
                          ['2018-12-10 13:53:06', 21.2],  
                     ]);  
        var options = {
          title: 'Lämpötila (ºC)',
          curveType: 'function',
          legend: { position: 'left' },
          hAxis: { textPosition: 'none',  title: 'Aika' },
          backgroundColor: 'transparent',
          colors:['green','#004411','Black']
        };

        var chart = new google.visualization.LineChart(document.getElementById('Lampo_chart'));
        chart.draw(data, options);
      }

           function ValoChart()  
           {  
                var data = google.visualization.arrayToDataTable([  
                          ['Valo', ''],  
                          ['2018-12-10 13:53:06', 627],  
                     ]);  
        var options = {
          title: 'Valo (lux)',
          curveType: 'function',
          legend: { position: 'left' },
          hAxis: { textPosition: 'none',  title: 'Aika' },
          backgroundColor: 'transparent',
          colors:['blue','#004411','Black']
          
        };

        var chart = new google.visualization.LineChart(document.getElementById('Valo_chart'));
        chart.draw(data, options);
      }

           function KosteusChart()  
           {  
                var data = google.visualization.arrayToDataTable([  
                          ['Kosteus', ''],  
                          ['2018-12-10 13:53:06', 81],  
                     ]);  
        var options = {
          title: 'Kosteus (%)',
          curveType: 'function',
          legend: { position: 'left' },
          hAxis: { textPosition: 'none',  title: 'Aika' },
          backgroundColor: 'transparent',
          colors:['red','#004411','Black']
          
        };

        var chart = new google.visualization.LineChart(document.getElementById('Kosteus_chart'));
        chart.draw(data, options);
      }
 
    </script>


    <table>
    <td><div id="Lampo_chart" style="width: 550px; height: 400px" ></div></td>
    <td><div id="Valo_chart" style="width: 550px; height: 400px"></div></td>
    <td><div id="Kosteus_chart" style="width: 550px; height: 400px"></div></td>
    </table>
</head>

 
<form action="Sensoriarvot.php" method="post">
<input type="hidden" name="hattu" value=1><br>
<input type="submit" value="Päivitä sensoriarvot">
<style>
#c4ytable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
}
#c4ytable td, #c4ytable th {
    border: 1px solid #ddd;
    padding: 8px;
}
 
#c4ytable tr:nth-child(even){background-color: #f2f2f2;}
 
#c4ytable tr:hover {background-color: #ddd;}
 
#c4ytable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #00A8A9;
    color: white;
}
input[type=submit] {
	-moz-box-shadow:inset 0px 1px 0px 0px #00a9a9;
	-webkit-box-shadow:inset 0px 1px 0px 0px #00a9a9;
	box-shadow:inset 0px 1px 0px 0px #00a9a9;
	background-color:#00a9a9;
	-moz-border-radius:6px;
	-webkit-border-radius:6px;
	border-radius:6px;
	border:1px solid #000000;
	display:inline-block;
	cursor:pointer;
	color:#ffffff;
	font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
	font-size:16px;
    font-weight:bold;
	padding:6px 24px;
	text-decoration:none;
	text-shadow:0px 1px 0px #00a9a9;
}
}
</style>

</form> 
 
 <br>
<TABLE id='c4ytable'><TR><TH>ID</TH><TH>Kosteus (%)</TH><TH>Lämpö (?)</TH><TH>Valo (lux)</TH><TH>Aikaleima</TH></TR><TR><TD>1</td><TD>81</td><TD>21.2</td><TD>627</td><TD>2018-12-10 13:53:06</td></TABLE>
</body>
</html>