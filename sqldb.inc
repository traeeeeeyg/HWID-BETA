#include <sqlx>

// Initialize the SQLite database connection
new dbHandle;
sqlx_connect("hwids.db", "my_secret_password", dbHandle);

// Function to insert a new HWID entry into the database
InsertHWID(clientName[], hwid[]) {
    new query[128];
    format(query, sizeof(query), "INSERT INTO hwids (client_name, hwid) VALUES ('%s', '%s')", clientName, hwid);
    sqlx_query(dbHandle, query);
}

// Function to retrieve all HWID entries from the database
GetHWIDs() {
    new query[128] = "SELECT * FROM hwids";
    new result;
    sqlx_query(dbHandle, query, result);
    while (sqlx_fetch_row(result)) {
        new clientName[32], hwid[128], timestamp[32];
        sqlx_get_string(result, 1, clientName, sizeof(clientName));
        sqlx_get_string(result, 2, hwid, sizeof(hwid));
        sqlx_get_string(result, 3, timestamp, sizeof(timestamp));
        print("Client: %s, HWID: %s, Timestamp: %s", clientName, hwid, timestamp);
    }
    sqlx_free_result(result);
}