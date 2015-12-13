# vsockets tools README #

VMware Player/Workstation/ESXi supports “VMware vsockets”, which a vendor-specific socket interface for communication between the host and the guest machine

* not to be confused with TCP/IP sockets
* vsockets have a different address familly

VMware Player has port “vsockets[connection-oriented]/976” open, for communication with the guest OS and the VMware tools running in the guest

### What is this repository for? ###

* Quick summary
   * Network tools for VMware vsockets
* Version: 0.1
   * working on Linux
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)
* Tools:
   * vsockets_nc
   * vsockets_hostname

### How do I get set up? ###

* Summary of set up
* Configuration
* Dependencies
* Database configuration
* How to run tests
* Deployment instructions

### "vsockets_nc" Usage guidelines ###

/// Ligação guest => host

~~~~
[root@localhost:/vmfs/volumes/5548c165-50642975-ae44-000c29bd161f/ftp] ./vsockets_nc -l 5000
VMware vsockets environment properties
=======================================
vmci address familly=56
vmci is present
vmci local CID=2
vmware ESXi host machine detected (CID=0)
vmci listening in port 5000
vmci socket=5
...listening in port:5000
Accepted connection from CID=942803562 , port=1029
Read 3 bytes from channel 1
oi
Wrote 3 bytes to channel 2
Read 9 bytes from channel 1
como vai
Wrote 9 bytes to channel 2
o hospedeiro vai bem
Read 21 bytes from channel 2
Wrote 21 bytes to channel 1
~~~~


//// Erro quando o CID remoto não existe

~~~~
[root@localhost:/vmfs/volumes/5548c165-50642975-ae44-000c29bd161f/ftp] ./vsockets_nc -c 942893562 -s 7000
VMware vsockets environment properties
=======================================
vmci address familly=56
vmci is present
vmci local CID=2
vmware ESXi host machine detected (CID=0)
...Connecting to CID=942893562 : Port:7000
vmci connecting to=[CID]942893562:7000
vmci socket=5
connect: Invalid argument
Closing vmci socket 5
...Connection failed: Invalid argument
~~~~

/// Ligação  host => guest

~~~~
[root@localhost:/vmfs/volumes/5548c165-50642975-ae44-000c29bd161f/ftp] ./vsockets_nc -c 942803562 -s 7000
VMware vsockets environment properties
=======================================
vmci address familly=56
vmci is present
vmci local CID=2
vmware ESXi host machine detected (CID=0)
...Connecting to CID=942803562 : Port:7000
vmci connecting to=[CID]942803562:7000
vmci socket=5
...Connection established to CID=942803562 : Port:7000
~~~~


### ESXi port scans ###

* guest => CID=2 : só vê os portos novos abertos pelo vsockets_nc
* guest => CID=0 : vê o porto 976 aberto
* guest => guest : só vê os portos novos abertos pelo vsockets_nc

* host => guest : só vê os portos novos abertos pelo vsockets_nc
   * (fica muito lento, o ESXi deve dar pouca prioridade a processos lançados na linha de comandos)

* host => CID=0 : não vê nenhum porto aberto
   * (fica muito lento, o ESXi deve dar pouca prioridade a processos lançados na linha de comandos)

* host => CID=2 : vê porto 2222 aberto


### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact