document.addEventListener('DOMContentLoaded', function() {
    let role = document.querySelector("#role");
    let name = document.querySelector("#name");

    const previousRole = localStorage.getItem('#role');
    console.log(previousRole);
    if (previousRole) {
        role.value = previousRole;
    }

    role.addEventListener('input', refresh);
    name.addEventListener('input', refresh);

    function refresh() {
        let xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    let json = JSON.parse(xhr.responseText);
                    let table = document.querySelector("table");
                    while (table.rows.length > 1) {
                        table.deleteRow(1);
                    }
                    json.forEach(function(thing) {
                        console.log(thing);
                        let row = table.insertRow(-1);
                        let cell1 = row.insertCell(0);
                        cell1.textContent = thing.name;
                        let cell2 = row.insertCell(1);
                        cell2.textContent = thing.username;
                        let cell3 = row.insertCell(2);
                        cell3.textContent = thing.age;
                        let cell4 = row.insertCell(3);
                        cell4.textContent = thing.role;
                        let cell5 = row.insertCell(4);
                        cell5.textContent = thing.email;
                        let cell6 = row.insertCell(5);
                        cell6.textContent = thing.webpage;
                        let actionCell = row.insertCell(6);
                        actionCell.innerHTML = `<a href=updateUser/updateUser.html?id=${thing.userID}><i class="fa-solid fa-pen"></i></a>
                                                &nbsp;&nbsp;
                                                <a href=deleteUser/deleteUser.html?id=${thing.userID}><i class="fas fa-trash"></i></a>`;
                    });
                } else {
                    console.error('HTTP error! status:', xhr.status);
                }
            }
        };
        xhr.open('GET', `index.php?role=${role.value}&name=${name.value}`, true);
        xhr.send();
    }

    document.querySelector("#role").addEventListener("input", async function() {
        await refresh();
        localStorage.setItem('#role', role.value);
    });
    document.querySelector("#name").addEventListener("input", async function() {
        await refresh();
    });

    refresh();
});