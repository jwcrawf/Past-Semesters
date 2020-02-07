//the prices of the boat
//1 Jameis 2 Gillum 3 Bowden
//4 CString 5 Renegade 6 Raven
var boat_prices = new Array();
boat_prices["0"]=0.00;
boat_prices["Jameis"]=600.00;
boat_prices["Gillum"]=650.00;
boat_prices["Bowden"]=900.00;
boat_prices["CString"]=950.00;
boat_prices["Renegade"]=1200.00;
boat_prices["Raven"]=6000.00;

//the prices of the packages
//1 Half day 2 Full day 3 Deep sea
//4 Dinner 5 Night 6 Spearfishing
var package_prices = new Array();
package_prices["None"]=0.00;
package_prices["Half Day"]=450.00;
package_prices["Full Day"]=600.00;
package_prices["Deep Sea"]=650.00;
package_prices["Dinner"]=550.00;
package_prices["Night"]=450.00;
package_prices["Spearfishing"]=600.00;

//gets the price of the boat
//from the radio buttons on the
//packages pages
function getBoatPrice() {
	var boatRadio = document.getElementsByName('selectedBoat');

	for (i=0; i < boatRadio.length; i++) {
		if (boatRadio[i].checked) {
			user_input = boatRadio[i].value;
		}
	}

	return boat_prices[user_input];
}


//gets the price from the package drop downs
function getPackagePrice() {
	var packageSelect = document.getElementById('package');

	return package_prices[packageSelect.value];
}

//gets the price from the selected boat
//in the dropdown on the admin page
function getBoatDropPrice() {
	var boatSelect = document.getElementById('boat');

	return boat_prices[boatSelect.value];
}

//calculates to total of package and price, adding sales tax
//originally output to the packages pages
function calculateTotal() {
	var total = (getBoatPrice() + getPackagePrice()) * 1.07;
	
	var totalEl = document.getElementById('totalPrice');

	document.getElementById('totalPrice').innerHTML = "Your Total is: $" + total.toFixed(2).replace(/\d(?=(\d{3})+\.)/g, '$&,') + "\n (Includes Sales Tax)";
	totalEl.style.display = 'block';
}

//calculates to total of package and price, adding sales tax
//outputs to the reservation page
function calculateResTotal() {
	var total = (getBoatDropPrice() + getPackagePrice()) * 1.07;
	
	var totalEl = document.getElementById('totalPrice');

	document.getElementById('totalPrice').innerHTML = "Your Total is: $" + total.toFixed(2).replace(/\d(?=(\d{3})+\.)/g, '$&,') + "\n (Includes Sales Tax)";
	totalEl.style.display = 'block';
}

//this function returns the total to the admin page for processing to the database
//please appreciate how this works, without ajax
function adminTotal() {
	var total = (getBoatDropPrice() + getPackagePrice()) * 1.07;
	total *= 100;
	total = Math.ceil(total);
	total /= 100;
	if(total.toFixed) {
		total = total.toFixed(2);
	}
	
	var totalEl = document.getElementById('totalPrice');

	document.getElementById('totalPrice').value = total;
	totalEl.style.display = 'block';
}

//hides total until there's a value to show
function hideTotal() {
	var totalEl = document.getElementById('totalPrice');
	totalEl.style.display = 'none';
}
