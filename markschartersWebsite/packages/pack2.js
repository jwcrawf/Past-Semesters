var boat_prices = new Array();
boat_prices["Jameis"]=600.00;
boat_prices["Gillum"]=650.00;
boat_prices["Bowden"]=900.00;
boat_prices["Theory"]=950.00;
boat_prices["Renegade"]=1200.00;
boat_prices["Raven"]=6000.00;

var package_prices = new Array();
package_prices["None"]=0.00;
package_prices["Half"]=450.00;
package_prices["Full"]=600.00;
package_prices["Deep"]=650.00;
package_prices["Dinner"]=550.00;
package_prices["Night"]=450.00;
package_prices["Spear"]=600.00;

function getBoatPrice() {
	var boatRadio = document.getElementsByName('selectedBoat');

	for (i=0; i < boatRadio.length; i++) {
		if (boatRadio[i].checked) {
			user_input = boatRadio[i].value;
		}
	}

	return boat_prices[user_input];
}

function getPackagePrice() {
	var boatSelect = document.getElementById('package');



	return package_prices[boatSelect.value];
}


function getBaitPrice() {
	var fishBait = document.getElementById('includebait');

	if(fishBait.checked) {
		return(40.00);
	} else {
		return(0.00);
	}
}

function calculateTotal() {
	var total = (getBoatPrice() + getPackagePrice() + getBaitPrice()) * 1.07;
	
	var totalEl = document.getElementById('totalPrice');

	document.getElementById('totalPrice').innerHTML = "Your Total is: $" + total.toFixed(2).replace(/\d(?=(\d{3})+\.)/g, '$&,') + "\n (Includes Sales Tax)";
	totalEl.style.display = 'block';
}

function hideTotal() {
	var totalEl = document.getElementById('totalPrice');
	totalEl.style.display = 'none';
}
