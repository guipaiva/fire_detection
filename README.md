# Fire Detection
Sensor nodes fire detection system simulator. Using threads in C.

## Description
This program simulates a fire detection system in a 30x30 forest, where we have 100 sensor nodes. Each sensor node is resposible to monitor 1 block around it and spread the message until it get to border nodes, which are able to communicate to the Central Thread. Only the nodes in the border are able to communicate to the Central Thread.

### Fire

The fire appears in a random position every 3 seconds. If in this position there is a sensor node, it will be destroyed and a 'X' will be displayed there. Otherwise the fire will be displayed as a red '@'. A text file will be generated to log destroyed nodes. 

### Sensor Nodes

Sensor nodes are displayed as 'T'. In this program there's a thread running for each sensor node. Every 1 second the node search around it for fire. If the node detects a fire or receive a message, it will communicate to the neighbour<sup id="a1">[1](#f1)</sup> nodes.

### Communication

The message is a int array that contains the ID of the node that detected the fire, the fire coordinates, and the time that the fire was detected.

### Central Thread

The central thread receives messages from the border nodes, write them into a log file, and then calls a firefighter to extinguish the fire in that location. 


### Execution

Compile the code:
```bash
gcc -o main main.c functions.c -pthread
```
And execute:
```bash
./main
```

##### Footnote
> <b id="f1">1</b> Neighbours are nodes that are three elements away from the message source, that is, diagonal nodes are not considered. [↩](#a1)
