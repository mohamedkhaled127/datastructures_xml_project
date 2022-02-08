import xml.etree.ElementTree as ET
import networkx as nx
import matplotlib.pyplot as plt

print("Please enter The Path of XML.")
G = nx.DiGraph()
path=input()
tree=ET.parse(path)
#tree = ET.parse('sample.xml')
root = tree.getroot()
for user in root:
    id = user[0].text
    print("id :", id)
    G.add_node(id, name = user[1].text)
    for follower in user[3]:
        fid = follower[0].text
        print(fid)
        G.add_edge(fid, id)


nx.draw(G, with_labels = True)
plt.savefig('foo.png')
plt.show()

