// hwid_logger.sma

#include <sqldb>

new const PLUGIN_NAME[] = "HWID Logger"
new const PLUGIN_VERSION[] = "1.0"
new const PLUGIN_AUTHOR[] = "xLEENER"

new Handle:g_hDatabase

public plugin_init()
{
    register_plugin(PLUGIN_NAME, PLUGIN_VERSION, PLUGIN_AUTHOR)
    
    // Initialize the SQLite database connection
    g_hDatabase = SQL_DBConnect("hwid_logger", "hwid_logger.db")
    
    if (g_hDatabase == INVALID_HANDLE)
    {
        set_fail_state("Failed to connect to database")
    }
}

public plugin_end()
{
    // Close the SQLite database connection
    SQL_DBDisconnect(g_hDatabase)
}

public client_putinserver(client)
{
    // Get the client's HWID
    new hwid[64]
    get_user_hwid(client, hwid, charsmax(hwid))
    
    // Log the HWID to the database
    new query[128]
    formatex(query, charsmax(query), "INSERT INTO hwids (hwid) VALUES ('%s')", hwid)
    SQL_DBQuery(g_hDatabase, query)
}