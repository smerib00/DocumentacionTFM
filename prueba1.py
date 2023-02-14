#!/usr/bin/python

from mininet.net import Mininet
from mininet.node import Controller
from mininet.cli import CLI
from mininet.link import Intf
from mininet.log import setLogLevel, info

def prueba1():

    net = Mininet( topo=None, build=False)

    info( '*** Añadiento controlador ***\n' )
    net.addController(name='c0')

    info( '*** Añadiendo switches ***\n')
    s1 = net.addSwitch('s1')
    Intf( 'eth1', node=s1 )

    info( '*** Añadiendo host ***\n')
    h1 = net.addHost('h1', ip='0.0.0.0')

    info( '*** Añadiento enlaces ***\n')
    net.addLink(h1, s1)

    info( '*** Iniciando red ***\n')
    net.start()
    h1.cmdPrint('dhclient '+h1.defaultIntf().name)
    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    prueba1()
