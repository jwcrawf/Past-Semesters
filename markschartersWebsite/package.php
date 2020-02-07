


<body onload='hideTotal()'>
  <script src="pack2.js"></script>
<link rel="stylesheet" href="package.css">
  <div class="wrap" id="wrap">
      <form action="" id="boatform" onsubmit="return false;">
      <div> 
          <div class="cont_order">
             <fieldset>
              <legend>Quick Estimate Calculator</legend>
              <label >Pick your boat:</label>
              <label class='radiolabel'><input type="radio"  name="selectedBoat" value="1" onclick="calculateTotal()" />The Famous Jameis:  Holds up to 8 people (+$600)</label><br/>
              <label class='radiolabel'><input type="radio"  name="selectedBoat" value="2" onclick="calculateTotal()" />The Gallant Gillum: Holds up to 10 people (+$650)</label><br/>
              <label class='radiolabel'><input type="radio"  name="selectedBoat" value="3" onclick="calculateTotal()" />Off The Bowden:     Holds up to 14 people (+$900)</label><br/>
              <label class='radiolabel'><input type="radio"  name="selectedBoat" value="4" onclick="calculateTotal()" />C-String Theory:    Holds up to 18 people (+$950)</label><br/>
              <label class='radiolabel'><input type="radio"  name="selectedBoat" value="5" onclick="calculateTotal()" />The Renegade:     Holds up to 24 people (+$1200)</label><br/>
              <label class='radiolabel'><input type="radio"  name="selectedBoat" value="6" onclick="calculateTotal()" />The Rock Raven:     Holds up to 120 people (+$6000)</label><br/>
              <br/>
               
              <label >Pick package</label>
       
              <select id="package" name='package' onchange="calculateTotal()">
              <option value="None">Select Package</option>
              <option value="1">Half Day Soiree (+$450)</option>
              <option value="2">Full Day ($600)</option>
              <option value="3">Deep Sea ++ ($650)</option>
              <option value="4">Fish and Dinner ($550)</option>
              <option value="5">Night Excursion ($450)</option>
              <option value="6">Fear the Spearfishing ($600)</option>
              
             </select>
              <br/>
               
              <div id="totalPrice"></div>
              
              </fieldset>
          </div>
             
     </form>
</div><!--End of wrap-->

</body>
</div>

