### Kubernetes concepts

Overview
    The leading container orchestration tool.
    Vendor neutral and open source.
    Runs on all major cloud providers.
    Provides a unified API.

Capabilities
    Service discovery and load balancing.
    Storage orchestration.
    Automated rollouts and rollbacks.
    Self-healing (restarting/replacing failed containers).
    Secret and configuration management.

Limitations
    Does not deploy or build applications or containers.
    Does not provide application-level services (e.g., native cache, databases, or message buses).

---

### Architecture

1. The Control Plane (Master)
    The Control Plane makes global decisions about the cluster and detects/responds to events.

    - kube-apiserver: It is the central hub that all components and users (via kubectl) talk to.

    - etcd: A consistent and highly-available key-value store that holds all cluster data. It serves as source of truth.

    - kube-scheduler: It watches for new Pods and assigns them to a specific Node based on resource availability.

    - kube-controller-manager: It runs control loops to ensure the current state of the cluster matches the desired state (e.g., if a node goes down, it notices and starts new pods).

    - cloud-controller-manager: It links your cluster into your cloud provider's API (AWS, GCP, Azure) to manage things like load balancers and storage.


2. Worker Nodes

    These are the machines (VMs or physical servers) that actually run your applications.

    - Kubelet: An agent that runs on each node to ensure that the containers described in Pod specifications are running and healthy. It manage pods lifecycle.

    - Kube-proxy: It maintains network rules on nodes, allowing network communication to your Pods from inside or outside the cluster.

    - Container Runtime: The software responsible for actually running the containers (e.g., containerd, CRI-O).

    - Pod: The smallest unit in Kubernetes; a wrapper that hosts one or more containers.


How they work together

    User sends a command (e.g., kubectl apply) to the API Server.
    The API Server updates etcd.
    The Scheduler notices the new requirement and picks a Worker Node.
    The Kubelet on that node receives the instruction and tells the Container Runtime to start the container.
    Kube-proxy sets up the networking so users can reach the app.


Hierarchical structure
cluster -> nodes -> pods -> containers

---

### Context

A context is a group of access parameters that defines which cluster, user, and namespace kubectl commands should target.

FILE LOCATION:
The configuration is typically stored in: $HOME/.kube/config (YAML format).

COMPONENTS:
- Cluster: The specific Kubernetes cluster.
- User: The credentials used to authenticate.
- Namespace: The default namespace for the context.

CLI COMMANDS:
- View current context:
  kubectl config current-context

- List all contexts:
  kubectl config get-contexts

- Switch context:
  kubectl config use-context <context-name>

- Delete a context:
  kubectl config delete-context <context-name>

- Rename a context:
  kubectl config rename-context <old-name> <new-name>

---

### Namespaces

DEFINITION
Namespaces are logical partitions within a single physical cluster used to group and isolate resources. They are commonly used to separate environments such as dev, test, and prod.

CORE CONCEPTS
- Logical Isolation: Used to group resources logically (dev, test, prod).
- Cascading Deletion: Deleting a namespace automatically deletes all objects within it.
- Connectivity: Objects in one namespace can typically access objects in other namespaces unless restricted.
- Policies: Network policies and resource quotas are defined at the namespace level.

YAML EXAMPLES

```yaml
1. Namespace Definition:
apiVersion: v1
kind: Namespace
metadata:
    name: prod

2. Pod Assignment:
apiVersion: v1
kind: Pod
metadata:
    name: application-name
    namespace: prod # Reference the namespace here
spec:
    containers:
    - name: nginx-container
      image: nginx
```

CLI COMMANDS (Alias: ns)
- List all namespaces:
  kubectl get ns

- Create a namespace:
  kubectl create ns <namespace-name>

- Delete a namespace:
  kubectl delete ns <namespace-name>

- Switch current context namespace:
  kubectl config set-context --current --namespace=<namespace-name>

- List pods in a specific namespace:
  kubectl get pods -n <namespace-name>

- List pods in all namespaces:
  kubectl get pods --all-namespaces

---

### Create resources

1. DECLARATIVE (Recommended)
- Method: Uses YAML files and 'kubectl apply' or 'create' to define the "Desired State."
- Benefits: Repeatable, version-controllable (GitOps), and portable.
- Sources: Official kubernetes.io documentation or IDE extensions (VS Code).

2. IMPERATIVE
- Method: Direct 'kubectl' commands.
- Best Use: Learning, rapid development, and troubleshooting.

CLI COMMANDS
- Create from file:
  kubectl create -f <yaml-file>

- List deployments:
  kubectl get deploy

- Delete deployment:
  kubectl delete deploy <deploy-name>

---

### Run Kubernetes locally

docker desktop -> you can only run one node
microk8s, minikube, kind => you can run multiple nodes

---

### Nodes: master and worker architecture

### 1. Master nodes (Control plane)
The control plane manages the cluster's state. It is a best practice NOT to run application workloads on master nodes to ensure stability and security.

COMPONENTS:

- kube-apiserver: 
  - The cluster's REST interface and gateway. 
  - The ONLY component that communicates directly with etcd.
  - All clients (kubectl, users, and other components) interact through this API.

- etcd: 
  - A consistent, high-availability key-value store.
  - Acts as the "Single Source of Truth" for all cluster state data.
  - Note: Not to be used as a database for application-specific data.

- kube-controller-manager: 
  - The "Controller of Controllers."
  - Manages various control loops, including:
    - Node Controller: Manages node status.
    - Replication Controller: Maintains the correct number of pods.
    - Endpoints Controller: Populates endpoint objects (joining Services and Pods).
    - Service Account & Token Controllers: Manages API access tokens.

- cloud-controller-manager: 
  - Offloads cloud-specific control logic to interact with provider APIs (AWS, Azure, GCP, etc.).
  - Manages Node (deletion checks), Route (network infra), Service (Load Balancers), and Volume (provisioning) controllers.

- kube-scheduler: 
  - Assigns newly created Pods to specific Worker Nodes.
  - Factors in requirements: Resource needs, hardware/software constraints, Affinity/Anti-affinity, and data locality.

---

### 2. Worker nodes
Physical or virtual machines where the actual application containers run.

DEFAULT SERVICES (Managed by Master):

- Container Runtime: The engine that runs containers (e.g., containerd, CRI-O).
- Kubelet: 
  - The primary "node agent." 
  - Communicates with the API server to ensure containers in Pod specs are running and healthy.
- kube-proxy: 
  - A network proxy that maintains network rules on the node.
  - Enables communication to pods from inside or outside the cluster.

---

### 3. Node pools
Groups of VMs within a cluster that share the same configuration (size, OS, labels).

- Flexibility: A cluster can have multiple pools (e.g., one pool with high-CPU VMs and another with high-RAM).
- Scaling: Each pool can be autoscaled independently based on workload demand.

---

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
