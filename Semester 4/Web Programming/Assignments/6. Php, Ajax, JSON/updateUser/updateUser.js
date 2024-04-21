document.addEventListener('DOMContentLoaded', (event) => {
    const urlParams = new URLSearchParams(window.location.search);
    const id = urlParams.get('id');

    const xhr = new XMLHttpRequest();
    xhr.open('GET', `getUserData.php?id=${id}`);
    xhr.onload = function() {
        if (xhr.status === 200) {
            const user = JSON.parse(xhr.responseText);
            console.log(user);
            document.getElementById('id').value = id;
            document.getElementById('name').value = user.name;
            document.getElementById('username').value = user.username;
            document.getElementById('password').value = user.password;
            document.getElementById('age').value = user.age;
            document.getElementById('role').value = user.role;
            document.getElementById('email').value = user.email;
            document.getElementById('webpage').value = user.webpage;
        } else {
            throw new Error(`HTTP error! status: ${xhr.status}`);
        }
    };
    xhr.send();
});