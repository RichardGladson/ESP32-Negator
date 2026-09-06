#include <WiFi.h>
#include <esp_wifi.h>
#include <LittleFS.h>

// ================== CONFIG ==================
#define BUTTON_PIN 0  // Boot button on standard ESP32 boards (active LOW)
#define LED_PIN    2  // Onboard LED GPIO pin
const char* fakeSSIDs[1000] = {
    // 1-100
    "TellMyWiFiLoveHer", "Loading...", "Searching...", "WiFi_Goin_Down_For_Real", "GetYourOwnWiFi",
    "PrettyFlyForAWiFi", "HideYourKidsHideYourWiFi", "NoMoreMisterWiFi", "AbrahamLinksys", "JohnWilkesBooth",
    "BenjaminFranklinksys", "WinnebagoForCuties", "BillClinNet", "Router?IHardlyKnowHer!", "DropItLikeIt'sHotspot",
    "ItBurnsWhenIP", "WuTangLAN", "LAN_Solo", "ObiWanKenobi", "ThePingInTheNorth",
    "WinterIsConnecting", "HouseLANnister", "LordVoldemodem", "SilenceOfTheLANs", "KeepItOnTheDownload",
    "99ProblemsButWiFiAin'tOne", "EverydayImBuffering", "GirlsGoneWireless", "FormatC:", "Connecting...",
    "AccessDenied", "SearchingForNetwork...", "Wi-FiNotConnected", "NetworkNotFound", "IPFreely",
    "C:\\Wi-Fi", "404_WiFi_Not_Found", "Virus.exe", "TrojanHorse_Installer", "MalwareBytes_Test",
    "FBI_Surveillance_Van_4", "NSA_PRISM_Node_7", "CIA_Safehouse_WiFi", "MI6_Field_Office", "Area51_Alien_Uplink",
    "KGB_Listening_Post", "Interpol_Mobile_Unit", "SWAT_Command_Center", "SecretService_Hotspot", "Paranoid_Android",
    "GetOffMyLawn", "Yell_PooP_For_Password", "BringBeerToApt4B", "PayYourRentFirst", "StopStargazingAt3AM",
    "QuietDownNeighbors", "CleanYourRoomFirst", "WeCanHearYouSinging", "StopStealingMyPaper", "BarkingDogIn3C",
    "NachoWiFi", "TestingNetwork_DoNotJoin", "FreeWiFi_JustKidding", "BuyYourOwnRouter", "ClickHereForFreeMoney",
    "TotallyNotAWebTrap", "Unsecured_Public_WiFi", "Error_500_Internal_Server", "Rebooting_Please_Wait", "Out_Of_Bandwidth",
    "MomUseThisOne", "DadPressHereForInternet", "Grandma_Click_This", "LookMomNoWires", "NoFreeWiFiHere",
    "GoGoGadgetWiFi", "SuperFastUnicornNet", "PotatoPoweredRouter", "DialUp_56k_Sound", "IsThisTheRealLife",
    "OrIsThisJustFantasy", "CaughtInALANslide", "NoEscapeFromReality", "OpenYourAPIs", "LookUpToTheSkies",
    "ImJustABoorerBoy", "IGetanErrorValue", "EasyComeEasyGo", "LittleHighLittleLow", "AnyWayTheSignalBlows",
    "Doesn'tReallyMatterToMe", "Mama_JustKilledAWifi", "PutAModemToHisHead", "PulledMyTriggerNowHe'sDead", "WiFi_Life_Has_Just_Begun",
    "ButNowI'veGoneAndThrownItAllAway", "Mama_Ooh_Didn't_Mean_To_Make_You_Cry", "IfI'mNotConnectedThisTimeTomorrow", "CarryOn_CarryOn", "AsIfNothingReallyMatters",

    // 101-200
    "TheLANBeforeTime", "A_Linksys_To_The_Past", "Super_Mario_LAN", "TheFastAndTheFluoride", "GameOfPings",
    "SpamFolder", "ByteMe", "UncertaintyPrinciple", "SchrodingersCat_Alive", "SchrodingersCat_Dead",
    "404_Network_Unavailable", "Connecting_To_5G_Tower", "Covid_Vaccine_Chip_8492", "BillGatesMicrochip_Active", "Starlink_Beta_Tester",
    "Skynet_Global_Defense", "Cyberdyne_Systems_Guest", "Umbrella_Corp_Lab_3", "Aperture_Science_WiFi", "Black_Mesa_Research",
    "Weyland_Yutani_Corp", "Stark_Industries_Secure", "Wayne_Enterprises_Guest", "Oscorp_Network", "Initech_WiFi",
    "Dunder_Mifflin_Paper_Co", "Monsters_Inc_Scream_Net", "Krusty_Krab_Guest_WiFi", "Chum_Bucket_Free_WiFi", "Central_Perk_WiFi",
    "Paddy's_Pub_Free_LAN", "Los_Pollos_Hermanos", "Pizza_Planet_Driver", "Bikini_Bottom_Hotspot", "Daily_Bugle_Press_Net",
    "The_Matrix_Hub", "Zion_Mainframe", "Nebuchadnezzar_Bridge", "Anomalous_Materials_Lab", "Vault_101_Network",
    "Rapture_Bathysphere_AP", "Columbia_Sky_Net", "Gondor_Calls_For_WiFi", "Rohan_Will_Answer", "One_WiFi_To_Rule_Them_All",
    "Speak_Friend_And_Connect", "You_Shall_Not_Pass", "The_Shire_Public_Net", "Mordor_Guest_Hotspot", "Isengard_Tower_Net",
    "Millennium_Falcon_Cockpit", "Death_Star_Guest_WiFi", "Tardis_Temporal_Uplink", "Gallifrey_Core_Net", "Borg_Collective_Node",
    "USS_Enterprise_Bridge", "Starfleet_Command", "Deep_Space_Nine_Hub", "Klingon_Warship_WiFi", "Cyberman_Mainframe",
    "HAL_9000_Core", "Jarvis_System_Online", "Ultron_Global_Net", "WANDAVISION_1950s", "Batcave_Secure_Uplink",
    "S.H.I.E.L.D._Helicarrier", "HYDRA_Sub_Level_4", "Gotham_City_P.D.", "Arkham_Asylum_Guest", "Daily_Planet_Newsroom",
    "Daily_Daily_Buffering", "Hogwarts_Express_WiFi", "Ravenclaw_Tower_Net", "Gryffindor_Common_Room", "Slytherin_Dungeon_WiFi",
    "Hufflepuff_Kitchens", "Ministry_Of_Magic_AP", "Order_Of_The_Phoenix", "Death_Eater_Encrypted", "Diagon_Alley_Public",
    "Luke_I_Am_Your_WiFi", "Chewbacca_Roar_Sound", "Darth_Router", "R2D2_Beep_Boop", "C3PO_Protocol_Net",
    "Boba_Fett_Tracking", "Mandalorian_Way_Net", "This_Is_The_WiFi", "Grogu_Snack_Net", "Tatooine_Moisture_Farm",
    "Endor_Ewok_Village", "Hoth_Echo_Base_WiFi", "Bespin_Cloud_City", "Kamino_Cloning_Facility", "Mustafar_Mining_Co",
    "Jakku_Scavenger_Net", "Starkiller_Base_Core", "Resistance_Secret_Base", "First_Order_Dreadnought", "Coruscant_Underlevel",

    // 201-300
    "Apt_2A_Stop_Stomping", "Apt_3B_Your_Music_Is_Loud", "Apt_4C_Fix_Your_Sink", "Apt_5D_Smells_Like_Fish", "Apt_1B_Pay_Your_Rent",
    "Apt_2B_Stop_Dancing_At_2AM", "Apt_3C_Your_Dog_Barks", "Apt_4A_Vacuum_Earlier", "Apt_5A_Mow_The_Lawn", "Apt_6B_Close_Your_Blinds",
    "We_Can_Hear_You_Fighting", "We_Can_Hear_You_Snoring", "We_Can_Hear_Your_TV", "Your_Cat_Is_On_My_Balcony", "Stop_Leaving_Trash_Outside",
    "Clean_The_Shared_Hallway", "Turn_Off_Your_Alarm", "Who_Stole_My_Package?", "Return_My_Lawn_Mower", "Stop_Parking_In_My_Spot",
    "Spot_42_Is_Reserved", "Don't_Block_The_Driveway", "Your_Car_Alarm_Is_On", "Fix_Your_Muffler", "Nice_Pajamas_Neighbor", "I_See_You_In_Your_Kitchen",
    "Close_Your_Curtains", "Put_Some_Clothes_On", "Stop_Smoking_On_Balcony", "We_Know_You're_In_There",
    "Gimme_A_Beer_For_Password", "Password_Is_12345678", "Password_Is_Password", "Not_Free_Pay_Me", "Donate_To_My_WiFi_Fund",
    "WiFi_Costs_Money_Neighbor", "Go_To_The_Library", "Get_A_Job_Buy_WiFi", "Chipotle_Free_WiFi", "Starbucks_Guest_Hotspot",
    "McDonalds_Free_WiFi_2", "Walmart_Guest_Connect", "Target_Guest_Wi-Fi", "Subway_Sandwiches_Net", "Taco_Bell_Wi-Fi_Guest",
    "Burger_King_Guest", "Wendy's_Free_Hotspot", "Panera_Bread_WiFi", "Dunkin_Guest_Network", "Krispy_Kreme_Free",
    "Airport_Free_WiFi_30min", "Hotel_Guest_Room_404", "Plane_Inflight_WiFi", "Bus_Terminal_Public", "Train_Station_Free_Net",
    "Coffee_Shop_No_Laptops", "Library_Quiet_Zone", "Hospital_Guest_WiFi", "University_Student_Net", "Campus_Dorm_Room_312",
    "Gym_Free_WiFi_Guest", "Mall_Public_Hotspot", "Park_Free_City_WiFi", "Metro_Station_Connect", "Taxi_Free_Hotspot",
    "Buffering_Forever...", "Connecting_99%", "Connecting_0%", "Signal_Weak_Try_Again", "Out_Of_Range",
    "Packet_Loss_Detected", "DNS_Server_Down", "Gateway_Timeout_504", "Bad_Gateway_502", "Service_Unavailable_503",
    "Connection_Refused", "Network_Cable_Unplugged", "Hardware_Failure", "Corrupted_Data_Stream", "Dialing_Up_PPP",
    "Modem_Screech_Sound", "Baud_Rate_1200", "Baud_Rate_2400", "Baud_Rate_9600", "Baud_Rate_14400",
    "Baud_Rate_28800", "Baud_Rate_33600", "56k_V90_Modem", "ISDN_Dual_Channel", "DSL_Filter_Missing",
    "Broadband_Coax_Cable", "Fiber_Optic_Gigabit", "Satellite_Lag_1000ms", "Ethernet_Connected", "Wi-Fi_Protected_Setup",

    // 301-400
    "Nacho_WiFi_Bro", "Drop_It_Like_It's_Hotspot", "Connect_And_Die", "It_Hurts_When_IP", "Byte_Me_Hard",
    "C:\\Users\\Guest", "PING_Pong_Champion", "High_Latency_Warning", "Lag_Is_My_Excuse", "AFK_In_The_Kitchen",
    "No_Lag_Just_Bad", "Rage_Quit_Network", "Gamer_Zone_Do_Not_Enter", "100ms_Ping_Minimum", "FPS_Drop_Hotspot",
    "GG_WP_WiFi", "Noob_Free_Zone", "PWN3D_Your_Router", "L33T_HAXOR_NET", "All_Your_Base_Are_Belong",
    "Zero_Wing_Mainframe", "Leeroy_Jenkins_Net", "Over_9000_Megabits", "Arrow_To_The_Knee", "Fus_Ro_Dah_Net",
    "Cake_Is_A_Lie", "Do_A_Barrel_Roll", "All_Capped_Out", "Bandwidth_Hog", "Data_Limit_Reached",
    "Trojan.Win32.Generic", "Worm_Installer.vbs", "Ransomware_Decryptor", "Keylogger_Active", "Spyware_Node_12",
    "Rootkit_Driver_v2", "Adware_PopUp_Net", "Cryptojacking_Rig", "Bitcoin_Miner_Node", "Ethereum_Node_4",
    "Dark_Web_Entry_Node", "Onion_Router_Relay", "Silk_Road_3.0", "Tor_Exit_Node_84", "Encrypted_Vault_X",
    "Area_51_Hangar_18", "Roswell_Debris_Lab", "Skinwalker_Ranch_AP", "Men_In_Black_Hub", "Chupacabra_Tracker",
    "Loch_Ness_Sonar_Net", "Bigfoot_Cam_Stream", "Bermuda_Triangle_GPS", "Illuminati_Eye_In_Sky", "New_World_Order_Node",
    "Flat_Earth_Society", "Chemtrail_Control_Hub", "Hollow_Earth_Uplink", "Moon_Landing_Studio_4", "HAARP_Weather_Control",
    "Surveillance_Drone_404", "Pigeon_Cam_Feed_12", "Birds_Are_Not_Real", "Reptilian_Base_Alpha", "Matrix_Glitch_Detected",
    "Simulation_Server_84", "NPC_Spawn_Point", "Press_F_To_Connect", "Ctrl_Alt_Delete", "Alt_F4_For_Free_WiFi",
    "Sudo_Make_Me_WiFi", "Root_Access_Granted", "Chmod_777_Network", "Ping_Death_Vector", "SYN_Flood_Incoming",
    "DDoS_Target_Practice", "Port_8080_Open", "SSL_Certificate_Expired", "Man_In_The_Middle", "Packet_Sniffer_Pro",
    "ARP_Spoofing_Node", "MAC_Address_Cloned", "Default_Gateway_192.168.1.1", "127.0.0.1_Home_Sweet_Home", "Localhost_3000",
    "0.0.0.0_Anywhere", "255.255.255.0_Mask", "IPv6_Is_Too_Long", "Static_IP_Only", "DHCP_Scope_Full",

    // 401-500
    "Router_Pass_Is_Admin", "Admin_Admin_Default", "Change_Your_Password", "Unsecured_Router_LOL", "Thanks_For_The_Free_Net",
    "I_Stole_This_WiFi", "My_Neighbors_Are_Cool", "My_Neighbors_Pay_My_Bills", "Free_WiFi_For_Hot_Girls", "Single_And_Buffering",
    "Looking_For_WiFi_Love", "Swipe_Right_For_Password", "Tinder_Match_Hotspot", "Date_Me_For_Free_Net", "Lonely_Router_Needs_Friend",
    "Will_Work_For_WiFi", "Will_Trade_WiFi_For_Food", "Need_Coffee_Send_Password", "Send_Nudes_For_WiFi", "Buy_Me_Pizza_First",
    "Cat_Picture_Stream_Only", "Dog_Gifs_Express", "Meme_Factory_Network", "Rick_Astley_Free_Net", "Never_Gonna_Give_You_WiFi",
    "Never_Gonna_Let_You_Connect", "Never_Gonna_Run_Around_And_Buffer", "Never_Gonna_Make_You_Lag", "Never_Gonna_Say_Disconnect", "Never_Gonna_Tell_A_Lie_And_Drop_You",
    "Smells_Like_WiFi_Spirit", "Sweet_Child_Of_WiFi", "Stairway_To_Network", "Hotel_California_WiFi", "You_Can_Never_Disconnect",
    "Comfortably_Buffered", "Another_Brick_In_The_LAN", "Wish_You_Were_Connected", "Smack_My_Router_Up", "Insomnia_No_Sleep_Net",
    "Enter_Routerman", "Master_Of_Routers", "One_Click_Away", "Fade_To_Buffering", "Sympathy_For_The_Router", "Gimme_Shelter_And_WiFi",
    "Paint_It_Black_Net", "Born_To_Be_Wireless", "Highway_To_Hotspot", "Back_In_Black_Net", "Thunderstruck_WiFi",
    "Riders_On_The_Signal", "Light_My_Router", "Break_On_Through_To_WiFi", "Purple_Haze_Hotspot", "All_Along_The_Router",
    "Voodoo_Child_Net", "Bohemian_Rhapsody_Hub", "Don't_Stop_Buffering", "Go_Your_Own_WiFi", "Fleetwood_Mac_Address",
    "Rumours_Of_Free_WiFi", "Tiny_Router_Dancer", "Rocket_Man_Uplink", "Bennie_And_The_Pings", "Crocodile_Router",
    "Space_Oddity_WiFi", "Ground_Control_To_Major_Tom", "Ziggy_Stardust_Net", "Starman_In_The_Sky", "Heroes_For_One_Day",
    "Under_Pressure_Net", "Radio_Gaga_WiFi", "Another_One_Bites_The_Dust", "We_Will_Connect_You", "We_Are_The_Champions_Net",
    "Billie_Jean_IsNotMyWiFi", "Beat_It_Get_Off_My_Net", "Thriller_Night_WiFi", "Smooth_Operator_Net", "Careless_Whisper_WiFi",
    "Take_On_Me_WiFi", "Take_Me_On_Network", "Shine_On_You_Crazy_Router", "Time_Is_Buffering", "Money_Get_Away_Net",
    "Us_And_Them_WiFi", "Brain_Damage_Net", "Eclipse_Of_The_Signal", "Run_Like_Hell_WiFi", "The_Wall_Encrypted",
    "Ring_Of_Fire_Hotspot", "Walk_The_Line_Net", "Folsom_Prison_WiFi", "Jackson_Family_Net", "A_Boy_Named_WiFi",
    "Hurt_So_Good_WiFi", "Jack_And_Diane_Net", "Free_Bird_Solo_WiFi", "Sweet_Home_Alabama_AP", "Simple_Man_Network",

    // 501-600
    "The_Grown_Ups_Are_Talking", "Wireless_Distencing_6ft", "Wash_Your_Hands_Connect_Your_LAN", "Quarantine_Bandwidth", "Social_Distancing_Signal",
    "Virtual_Living_Room", "Zoom_Call_In_Progress", "Mute_Your_Mic", "Can_You_Hear_Me_Now?", "Screen_Share_Active",
    "You're_On_Mute", "Awkward_Silence_Network", "Breakout_Room_4", "Waiting_For_Host", "Meeting_ID_123_456",
    "End_Of_The_Internet", "Last_Router_On_The_Left", "There_Is_No_Spoon", "Follow_The_White_Rabbit", "Red_Pill_Blue_Pill_Net",
    "Enter_The_Matrix", "Agent_Smith_Monitoring", "Knock_Knock_Neo", "Zion_Mainframe_Node_2", "Construct_Loading...",
    "Jurassic_Park_Fence_Control", "Clever_Girl_WiFi", "Hold_Onto_Your_Butts", "Spared_No_Expense_Net", "Nedry_Access_Denied",
    "Ah_Ah_Ah_You_Didn't_Say_Magic_Word", "T-Rex_Paddock_Cam", "Dino_DNA_Sequencer", "Isla_Nublar_Guest", "Isla_Sorna_Research",
    "Back_To_The_Future_1.21GW", "88_Miles_Per_Hour", "Flux_Capacitor_Charging", "Great_Scott_Network", "Doc_Brown's_Lab",
    "McFly_Hoverboard_Net", "Biff's_Pleasure_Paradise", "Clock_Tower_Uplink", "DeLorean_Time_Circuits", "Plutonium_Core_Online",
    "Ghostbusters_Firehouse", "Who_You_Gonna_Call?", "Slimer's_Ecto_Net", "Stay_Puft_Marshmallow", "Proton_Pack_Charged",
    "Don't_Cross_The_Streams", "Zuul_Gatekeeper_AP", "Keymaster_Vinz_Clortho", "Ecto_1_Mobile_Node", "Gozer_The_Destructor",
    "Men_In_Black_Neuralyzer", "Flash_Memory_Erased", "Noisy_Cricket_Net", "Edgar_Sugar_Water", "Galaxy_On_Orion's_Belt",
    "MIB_Headquarters_NYC", "Alien_Registration_Net", "Post_Office_Sorting_Alien", "Worm_Guys_Breakroom", "Frank_The_Pug_WiFi",
    "E.T._Phone_Home_WiFi", "Elliot's_Reese's_Pieces", "Flying_Bicycle_Uplink", "Speak_And_Spell_Modem", "Alien_Quarantine_Zone",
    "Close_Encounters_5_Notes", "Mothership_Beam_Me_Up", "Crop_Circle_Generator", "Abduction_Beam_Active", "Roswell_Incident_1947",
    "Area_51_S4_Facility", "Groom_Lake_Flight_Test", "Majestic_12_Encrypted", "Project_Blue_Book_File", "Interstellar_Black_Hole",
    "Event_Horizon_Drive", "Gargantua_Gravitational", "Murph_Don't_Let_Me_Leave", "TARS_Humor_Setting_75%", "CASE_Navigation_Hub",

    // 601-700
    "Iron_Man_Mark_85", "I_Am_Iron_WiFi", "Love_You_3000", "Cap's_Vibranium_Shield", "I_Can_Do_This_All_Day", "On_Your_Left",
    "Mjolnir_Authentication", "Worthy_Devices_Only", "Point_Break_Thor", "Strongest_Avenger_Login", "Hulk_Smash_Router",
    "Always_Angry_Net", "Hawkeye_Never_Misses", "Black_Widow_Red_Room", "Spider_Man_Web_Slinger", "Peter_Parker's_Hotspot",
    "With_Great_Bandwidth", "Comes_Great_Responsibility", "Uncle_Ben's_Legacy", "Friendly_Neighborhood_Net", "Multiverse_Of_Madness",
    "Doctor_Strange_Sanctum", "Eye_Of_Agamotto_Uplink", "Dormammu_I've_Come_To_Bargain", "Mirror_Dimension_AP", "Wakanda_Forever_Net",
    "Vibranium_Core_Network", "Kimoyo_Bead_Uplink", "Black_Panther_Habit", "Ancestral_Plane_WiFi", "Guardians_Of_The_Galaxy",
    "I_Am_Groot_Net", "We_Are_Groot", "Dance_Off_Bro", "Star_Lord's_Zune", "Rocket_Raccoon_Tech", "Drax_The_Invisible",
    "Thanos_Snap_50%_Packet_Loss", "I_Am_Inevitable", "And_I_Am_Iron_Man", "Infinity_Gauntlet_Hub", "Space_Stone_Teleport",
    "Mind_Stone_Vision", "Reality_Stone_Aether", "Power_Stone_Orb", "Time_Stone_Loop", "Soul_Stone_Vormir",
    "Justice_League_Watchtower", "Hall_Of_Justice_Guest", "Superman_Fortress_Solitude", "Krypton_Core_Net", "Kryptonite_Shielded",
    "Batman_Batcomputer_Main", "Alfred's_Tea_Service", "Robin_Boy_Wonder_Net", "Nightwing_Bludhaven", "Red_Hood_Under_Control",
    "Wonder_Woman_Themyscira", "Lasso_Of_Truth_Auth", "Flash_Speed_Force_Gbit", "Fastest_Net_Alive", "Aquaman_Atlantis_Depth",
    "Trident_Of_Atlan", "Cyborg_Mother_Box", "Green_Lantern_Sector_2814", "Beware_My_Power", "In_Brightest_Day_WiFi",
    "In_Blackest_Night_Net", "Shazam_Magic_Word", "Black_Adam_Kahndaq", "Suicide_Squad_TaskForceX", "Amanda_Waller_Encrypted",
    "Peacemaker_Eagle_Net", "Eagly's_Perch_WiFi", "Harley_Quinn_Mallet", "Joker's_Funhouse_Free", "Penguin_Iceberg_Lounge",
    "Riddler_Riddle_Me_This", "Two_Face_50_50_Ping", "Scarecrow_Fear_Toxin", "Bane_Rising_Network", "Poison_Ivy_Greenhouse",

    // 701-800
    "Super_Mario_Bros_W1-1", "Princess_Is_In_Another_Castle", "Bowser's_Keep_Hotspot", "Yoshi's_Island_WiFi", "Toad's_House_Powerup",
    "Luigi's_Mansion_Haunted", "Wario_Gold_Mine", "Waluigi_Waaa_Net", "Donkey_Kong_Country", "DK_Banana_Hoard",
    "Diddy_Kong_Peanut_Pop", "Legend_Of_Zelda_TriForce", "Master_Sword_Pedestal", "Hyrule_Kingdom_Public", "Ganon's_Tower_Dark_Net",
    "Sheikah_Slate_Uplink", "Shrine_Of_Resurrection", "Korok_Seed_YaHaHa", "Navi_Hey_Listen_WiFi", "Epona's_Stable_Guest",
    "Pokemon_Center_Free_Heal", "Pikachu_Thunderbolt_5G", "Wild_WiFi_Appeared", "Gotta_Catch_Em_All", "Team_Rocket_Blasting_Off",
    "Prof_Oak's_Lab_Net", "Pallet_Town_Gateway", "Magikarp_Splash_No_Signal", "Charizard_Flame_Net", "Mewtwo_Secret_Lab",
    "Metroid_Samus_Varia_Suit", "Ridley's_Lair_Encrypted", "Chozo_Artifact_Uplink", "Sonic_Gotta_Go_Fast", "Green_Hill_Zone_Act_1",
    "Tails_Two_Tails_Net", "Knuckles_Angel_Island", "Chaos_Emerald_Power", "Eggman_Death_Egg_Main", "Dr_Robotnik_Badniks",
    "Street_Fighter_Hadouken", "Shoryuken_Upper_Cut", "Chun_Li_Spinning_Kick", "Guile_Theme_Goes_With_All", "M_Bison_Psycho_Power",
    "Mortal_Kombat_Finish_Him", "Fatality_Network", "Flawless_Victory_Net", "Get_Over_Here_Scorpion", "Sub_Zero_Freeze_Lag",
    "Raiden_Thunder_God", "Shang_Tsung_Soul_Mine", "Netherrealm_Portal", "Shaolin_Monk_Temple", "Outworld_Tournament",
    "Tekken_Iron_Fist", "Heihachi_Mishima_Net", "King_Jaguar_Roar", "Devil_Jin_Transformation", "Yoshimitsu_Manji_Clan",
    "Final_Fantasy_VII_Midgar", "Avalanche_Sector_7", "Shinra_Electric_Power", "Cloud's_Buster_Sword", "Sephiroth_One_Winged",
    "Chocobo_Stable_Free", "Moogle_Kupo_Network", "Materia_Slot_Active", "Limit_Break_Omnislash", "Gold_Saucer_Casino",
    "Kingdom_Hearts_Keyblade", "Destiny_Islands_WiFi", "Traverse_Town_Hub", "Organization_XIII_Node", "Heartless_Spawn_Point",

    // 801-900
    "SpongeBob_SquarePants", "Patrick_Star_Is_This_KrustyKrab", "No_This_Is_Patrick", "Squidward's_Clarinet_Solo", "Sandy's_Treedome_Net",
    "Plankton_Formula_Stealer", "Secret_Formula_Vault", "Jellyfish_Fields_Free", "Rock_Bottom_Buss_Stop", "Goo_Lagoon_Beach_WiFi",
    "Simpsons_742_Evergreen_Terrace", "D'oh_Network_Error", "Mmm_Forbidden_WiFi", "Kwik_E_Mart_Thank_You", "Moe's_Tavern_Duff_Beer",
    "Nuclear_Power_Plant_Sector_7G", "Springfield_Elementary", "Bart's_Skateboard_Net", "Lisa's_Saxophone_Jazz", "Homer's_Donut_Box",
    "Family_Guy_Quahog_Net", "Peter_Griffin_Hehehe", "Stewie_World_Domination", "Brian's_Novel_Draft", "Quagmire's_Giggity_Net",
    "South_Park_Colorado", "Oh_My_God_They_Killed_WiFi", "Respect_My_Authoritah", "Towelie_Don't_Forget_Towel", "Tegridy_Farms_WiFi",
    "Rick_And_Morty_Dimension_C137", "Pickle_Rick_Net", "Wubba_Lubba_Dub_Dub", "Portal_Gun_Green_Signal", "Get_Schwifty_Hotspot",
    "Plumbus_Factory_Net", "Meeseeks_Box_Look_At_Me", "Citadel_Of_Ricks", "Gazorpazorp_Network", "Birdperson's_Beacon",
    "Futurama_Planet_Express", "Bender_Bending_Rodriguez", "Bite_My_Shiny_Metal_Router", "Good_News_Everyone", "Fry's_Holophoner",
    "Leela's_One_Eye_View", "Professor_Farnsworth_Lab", "Zoidberg_Why_Not_WiFi", "MomCorp_Robot_Company", "NIBBLER_Dark_Matter",
    "Adventure_Time_Ooo", "Mathematical_Network", "Algebraic_Hotspot", "Finn_The_Human_Hero", "Jake_The_Dog_Stretch", "Marceline_Vampire_Queen", "Ice_King_Crown_Freeze", "Princess_Bubblegum_Lab", "BMO_Video_Game_Console", "Lumpy_Space_Princess_OhMyGlob",
    "Gravity_Falls_Mystery_Shack", "Dipper's_Journal_3", "Mabel's_Grappling_Hook", "Bill_Cipher_Triangle", "Gideon_Gleeful_Net",
    "Stan_Pines_Snoops_Free", "Ford_Pines_Portal", "Waddles_The_Pig_WiFi", "Gnome_Vomit_Rainbow", "Soos_Fix_It_Shop",
    "Avatar_Air_Nation", "Water_Tribe_South", "Earth_Kingdom_BaSingSe", "Fire_Nation_Attacks", "There_Is_No_War_In_BaSingSe",
    "Uncle_Iroh's_Tea_Shop", "Jasmine_Dragon_WiFi", "Cabbage_Man_My_Cabbages", "Appa_Yip_Yip_Signal", "Momo_Flying_Lemur",

    // 901-1000
    "Searching_For_Signals...", "Connecting_To_The_Matrix", "Signal_Found_Connecting", "Authenticating_User...", "Obtaining_IP_Address",
    "IP_Address_Collision", "DNS_Probe_Finished", "No_Internet_Secured", "Action_Required_Login", "Captive_Portal_Redirect",
    "Guest_Network_Isolation", "Bandwidth_Throttled_128k", "Data_Cap_Exceeded", "Fair_Usage_Policy_Applied", "WPA2_Personal_PSK",
    "WPA3_Enterprise_Encrypted", "AES_256_Bit_Cipher", "RADIUS_Server_Auth", "TKIP_Deprecated_Warn", "SSID_Broadcast_Disabled",
    "Hidden_Network_Click_To_Join", "MAC_Filter_Active", "Blacklisted_Device_Detected", "Rogue_AP_Scanner", "Deauth_Attack_In_Progress",
    "Handshake_Captured_WPA", "Aircrack_ng_Target", "Reaver_WPS_Attack", "Pineapple_WiFi_Trap", "Evil_Twin_Access_Point",
    "Man_In_The_Middle_Node", "Wireshark_Packet_Capture", "Promiscuous_Mode_On", "Monitor_Mode_Interface", "Packet_Injection_Active",
    "Kali_Linux_Pentest_Tool", "Metasploit_Framework_Net", "Nmap_Port_Scanner", "Burp_Suite_Proxy_Host", "OWASP_Top_10_Net",
    "Buffer_Overflow_Exploit", "SQL_Injection_Vector", "Cross_Site_Scripting_XSS", "Zero_Day_Vulnerability", "Patch_Your_System_Now",
    "Firmware_Update_Required", "Router_Reboot_Scheduled", "Factory_Reset_Button", "WPS_Button_Pressed", "Dual_Band_2.4G_5G",
    "5GHz_High_Speed_Channel", "6GHz_WiFi_6E_Ultra", "Beamforming_Targeting", "MU_MIMO_Multi_User", "Mesh_Node_Satellite_3",
    "Range_Extender_Repeater", "Powerline_Adapter_AV2", "Gigabit_Ethernet_Uplink", "Fiber_To_The_Home_FTTH", "Coaxial_DOCSIS_3.1",
    "Asymmetric_DSL_Line", "VDSL2_Vectoring_Node", "Dial_Up_56k_V92", "ISDN_PRI_Interface", "T1_Carrier_Line_1.5Mb", "T3_Pipe_45Mbps", "OC3_Optical_Carrier", "Dark_Fiber_Unlit", "Undersea_Cable_Gateway", "Satellite_Geostationary",
    "Starlink_Dishy_McFlatface", "Low_Earth_Orbit_LEO", "Kuiper_Sat_Constellation", "OneWeb_Network_Node", "Cellular_4G_LTE_Tower",
    "5G_NR_mmWave_Cell", "6G_Experimental_Node", "Bluetooth_LE_Beacon", "Zigbee_Smart_Home_Mesh", "Z_Wave_IoT_Network",
    "LoRaWAN_Gateway_868MHz", "RFID_Scanner_Node", "NFC_Proximity_Field", "LiFi_Optical_Light_Net", "Infrared_Data_IrDA",
    "Ultrawideband_UWB_Tag", "Sub_1GHz_Telemetry", "Ham_Radio_AX25_Packet", "Morse_Code_CW_Signal", "Shortwave_Number_Station",
    "UVB_76_Buzzer_Feed", "Pip_Number_Station", "Squeaky_Wheel_RF", "Lincolnshire_Poacher", "Cherry_Ripe_Transmission",
    "Automatic_Gain_Control", "Voltage_Controlled_Osc", "Phase_Locked_Loop_PLL", "Signal_To_Noise_Ratio", "Decibels_Per_Milliwatt",
    "Received_Signal_RSSI", "Quadrature_Amplitude_QAM", "Orthogonal_Frequency_OFDM", "Spread_Spectrum_FHSS", "Direct_Sequence_DSSS",
    "The_Final_SSID_1000", "End_Of_Array_Null", "String_Buffer_Overflow", "Array_Index_Out_Of_Bounds", "EOF_Reached_Goodbye"
};
int currentChannel = 1;
const int numSSIDs = sizeof(fakeSSIDs) / sizeof(fakeSSIDs[0]);

void sendBeacon(const char* ssid);

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);

  setCpuFrequencyMhz(240);
  // Clean start
  esp_wifi_stop();
  delay(100);
  WiFi.mode(WIFI_MODE_NULL);
  delay(100);

  WiFi.mode(WIFI_MODE_STA);
  esp_wifi_set_promiscuous(true);
  delay(200);

  uint8_t mac[6];

  unsigned long pressStartTime = 0;
  
  while (true) {
    // The boot button is active-LOW (reads LOW when pressed)
    if (digitalRead(BUTTON_PIN) == LOW) {
      if (pressStartTime == 0) {
        pressStartTime = millis(); // Start the timer on initial press
      } else if (millis() - pressStartTime >= 2000) {
        Serial.println("Hold detected! Proceeding to loop...");
        break; // Exit the setup block's blocking loop
      }
    } else {
      // Reset timer if the button is released prematurely
      pressStartTime = 0;
    }
    
    delay(20); // Prevent watchdog trigger and debounce slightly
  }

  // Turn LED on once the button check passes
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  for (int i = 0; i < numSSIDs; i++) {
    sendBeacon(fakeSSIDs[i]);
  }
}

void sendBeacon(const char* ssid) {
  int ssidLen = strlen(ssid);
  if (ssidLen > 32) ssidLen = 32;

  esp_wifi_set_channel(currentChannel, WIFI_SECOND_CHAN_NONE);

  uint8_t packet[200];  // bigger buffer to be safe
  int offset = 0;

  // Fixed beacon header
  packet[offset++] = 0x80;  // Management, Beacon
  packet[offset++] = 0x00;
  packet[offset++] = 0x00;  // Duration
  packet[offset++] = 0x00;

  // Destination = broadcast
  for (int i = 0; i < 6; i++) packet[offset++] = 0xFF;

  // Source MAC + BSSID (randomized)
  uint8_t mac[6];
  for (int j = 0; j < 6; j++) mac[j] = random(0, 256);
  for (int i = 0; i < 6; i++) packet[offset++] = mac[i];  // Source
  for (int i = 0; i < 6; i++) packet[offset++] = mac[i];  // BSSID

  packet[offset++] = 0x00;  // Sequence control low
  packet[offset++] = 0x00;

  // Timestamp (8 zero bytes is fine)
  for (int i = 0; i < 8; i++) packet[offset++] = 0x00;

  packet[offset++] = 0x64;  // Beacon interval low
  packet[offset++] = 0x00;  // high

  packet[offset++] = 0x01;  // Capability low (open)
  packet[offset++] = 0x04;  // high

  // === SSID IE ===
  packet[offset++] = 0x00;           // Element ID: SSID
  packet[offset++] = ssidLen;
  memcpy(&packet[offset], ssid, ssidLen);
  offset += ssidLen;

  // Supported Rates
  packet[offset++] = 0x01;
  packet[offset++] = 0x08;
  uint8_t rates[8] = {0x82, 0x84, 0x8b, 0x96, 0x12, 0x24, 0x48, 0x6c};
  memcpy(&packet[offset], rates, 8);
  offset += 8;

  
  packet[offset++] = 0x03;
  packet[offset++] = 0x01;
  packet[offset++] = currentChannel;   

  // Extended Supported Rates (helps a lot with modern phones)
  packet[offset++] = 0x32;
  packet[offset++] = 0x04;
  uint8_t ext_rates[4] = {0x0c, 0x18, 0x30, 0x60};
  memcpy(&packet[offset], ext_rates, 4);
  offset += 4;

  // Send it
  esp_err_t result = esp_wifi_80211_tx(WIFI_IF_STA, packet, offset, false);
  currentChannel++;
  
  if (currentChannel > 11) {
    currentChannel = 1;
  }
}