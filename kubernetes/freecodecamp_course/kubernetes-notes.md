### Kubernetes concepts

It is the leading container orchestration tool

It is vendor neutral, open source and run on all cloud providers

What it can do:

Service discovery and load balancing
Storage Orchestration
Rollouts and rollbacks
Self Healing
Secret and configuration management
It has an unified API

What it can't do:

Deploy or build application or containers

It doesn't provide application level services like cache, databases, or message buses

Architecture in details

##### todo

master node -> control plane
it runs controller and servier

container run in a pod -> pod run in a node -> node eun in cluster

##### todo

### Run kube locally

docker desktop => only one node

microk8s, minikube, kind => multiple node runnable

### Cli and context

kube-apiserver, desired state on a yaml file and send to api server via cli

kubectl -> it communicate with api server

### Context

configuration file is stoerd in $home/.kube/config -> YAML file
a group of access parameters to a k8 cluster
contain cluster, user and namespace, all kubectl command run against a cluster

kubectl config current-context
kubectl config get-contexts
kubectl config use-context <context-name>
kubectl config delete-context <context-name>
kubectl config rename-context <old-name> <new-name>

### Create resource in kube

declarative
using kubectl and yaml to define desired state
suggested to use since it's repeateble and movable
get template from kubernetes.io or directly from vscode

imperative
kubectl commands, great for learning, development and troubleshooting

deployments
kubectl create -f <yaml-file>
kubectl get deploy -> get deployment (pod) inside a cluster
kubectl delete deploy <deploy-name>

### Namespaces

allow group resources (dev, test, prod)

like logical namespace to group resources

delete namespace delete all child objects

object in one namespace cna acces objects in a != one

```yaml
# namespace definiton
apiVersion: v1
kind: Namespace
metadata:
    name: prod

# pod definition
apiVersion: v1
kind: Pod
metadata:
    name: application-name
    namespace: prod # referenced here
spec:
    containers:
    - name: nginx-container
      image: nginx
```

At a namespace leve you can set network policy definition and resource qoute definition

# ns is shortcut for namespaces

kubectl get ns
kubectl config set-context --current --namespace=<namespace-name> # used to change namespace in current context
kubeclt create ns <namespace-name>
kubeclt delete ns <namespace-name>
kubeclt get pods --all-namespaces
kubeclt get pods -n <namespace-name>

### Nodes

##### Master node => control plane

Contains:

- kube-controller-manager
- cloud-controller-manager
- kube-apiserver -> opnly component that communicate with etcd
- kube-scheduler
- etcd -> key value datasroe for cluster state data

Dont run application on the master node

#### kube-apiserver

Rest interface
save state to datasrtore
client interact with it and never direclty in the etcd

#### etcd

datastore oor storing cluster state
single source of truth
not a database or datastore for application to use

#### kube-control-manager

the controller of controllers
it runs controllers:

- node controller
- replication controller
- endpoints controller
- service account & token controllers

#### cloud-control-manager

interact with the cloud provider controllers

- node: chjeck provider to determine if a node has been deleted after stop responding
- route: settiung up routes in teh underlying dloud infrastructure
- sercvice: create updsate eleted cloud provider load balancer
- volume: create attach mounting volumens and interacting with the cloud provider to orchestrate volumes

#### kube-scheduler

watches new created pods and select a node for them to un on
scheduling decision policy

- resource requiresments
- hardware software policy contraints
- affinity of specifications
- data locality

##### Worker nodes

nodes are physical or virtual machines
nodes together forms a cluster
nosdes running the contianers

when adding a worker node to a cluster some kube services are added by default adn managed by the master node:

- container runtime
- kubelet -> manage pods lifecycle and ensure container in pods specs are running healthy
- kube-proxy -> network proxy, manage network rules on nodes

nodes pool
group of virtual machine, with all the same size
a cluster can have muiltple node pools:

- pools can hosts differnet size of vms
- each pool can be autoscaled independenlty from other pools

kubectl get nodes
kubeclt describe node <node-name> -> node name is optional

you can direclty commmunicate with orchestration deployed in the cloud

### Pods

represetn a unit of deployment and encapsulate a app contioner
smallest unit
run into nodes
can un one or multiple containers
container in a pod share:

- ip address space
- mounted volumes
  container in a pod can commuicate via localhost

ephemeral
don't update pod, you replace with new version (with new ip address)

you scale deploying more pods, not more containers inside the pod
