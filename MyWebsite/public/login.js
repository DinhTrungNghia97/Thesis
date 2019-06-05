var globalUsername = null;
var globalPassword = null;

var Auth_Username = firebase.database().ref().child("Username");
Auth_Username.on('value', function(snapshot){
globalUsername = snapshot.val();
});

var Auth_Password = firebase.database().ref().child("Password");
Auth_Password.on('value', function(snapshot){
globalPassword = snapshot.val();
});

function login() {	
	var InputUsername = document.getElementById('txt_username').value;
	var InputPassword = document.getElementById("txt_password").value;
	
	if (InputUsername == globalUsername) {
		if (InputPassword == globalPassword) {
			window.location.replace("data_monitor.html");
		}
		else {
			alert('Wrong Password');
		}
	}
	else{
		alert('Wrong Username');
	}
}

/*
firebase.auth().onAuthStateChanged(function(user) {
  if (user) {
    // User is signed in.
	alert('Sign-in');
  }
});
function login() {
	const email = txt_email.value;
	const pass = txt_password.value;
	const auth = firebase.auth();
	const promise = auth.signInWithEmailAndPassword(email, pass);
	promise.catch(function(error) {
		// Handle Errors here.
		var errorCode = error.code;
		var errorMessage = error.message;
		if (errorCode === 'auth/wrong-password') {
            alert('Wrong password.');
			return;
          } else {
            alert(errorMessage);
					console.log(error);
			return;
          }
});
}
*/