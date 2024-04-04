document.addEventListener("DOMContentLoaded", function() {
    start();
});

function start() {
    const tableData = [
        ["Rares", "Goia", 20],
        ["Tudor", "Pop", 21],
        ["Narcis", "Grecu", 23],
		["Andreea", "Badiu", 20],
		["Alexandru", "Moraru", 26],
    ];

    const tableContainer = document.getElementById("table-container");
    const table = document.createElement("table");
    const thead = document.createElement("thead");
    const tbody = document.createElement("tbody");

    const headerRow = document.createElement("tr");
    const headers = ["First Name", "Last Name", "Age"];
    headers.forEach(headerText => {
        const th = document.createElement("th");
        th.textContent = headerText;
        headerRow.appendChild(th);
    });
    thead.appendChild(headerRow);
    table.appendChild(thead);

    tableData.forEach(rowData => {
        const row = document.createElement("tr");
        rowData.forEach(cellData => {
            const cell = document.createElement("td");
            cell.textContent = cellData;
            row.appendChild(cell);
        });
        tbody.appendChild(row);
    });
    table.appendChild(tbody);

    tableContainer.appendChild(table);

    const headersList = table.querySelectorAll("th");
    headersList.forEach((header, index) => {
        header.addEventListener("click", () => {
            sortTable(index);
        });
    });
}

let ascending = true;

function sortTable(columnIndex) {
    const table = document.querySelector("table");
    const rows = Array.from(table.querySelectorAll("tbody > tr"));

    rows.sort((rowA, rowB) => {
        const cellA = rowA.querySelectorAll("td")[columnIndex].textContent;
        const cellB = rowB.querySelectorAll("td")[columnIndex].textContent;
        if (ascending) {
            return cellA.localeCompare(cellB);
        } else {
            return cellB.localeCompare(cellA);
        }
    });

    const tbody = table.querySelector("tbody");
    while (tbody.firstChild) {
        tbody.removeChild(tbody.firstChild);
    }

    rows.forEach(row => {
        tbody.appendChild(row);
    });

    ascending = !ascending;

    const headersList = table.querySelectorAll("th");
    headersList.forEach((header, index) => {
        header.textContent = header.textContent.replace(/ \u2191| \u2193/g, "");
        if (index === columnIndex) {
            header.textContent += ascending ? " \u2191" : " \u2193";
        }
    });
    
    if (sortedColumnIndex === columnIndex) {
        ascending = !ascending;
    } else {
        ascending = true;
    }
    sortedColumnIndex = columnIndex;
}
