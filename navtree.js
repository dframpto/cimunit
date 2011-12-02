var NAVTREE =
[
  [ "CIMUnit", "index.html", [
    [ "Main Page", "index.html", null ],
    [ "Related Pages", "pages.html", [
      [ "Todo List", "todo.html", null ]
    ] ],
    [ "Modules", "modules.html", [
      [ "cimunit_mutex Module", "group__cimunit__mutex.html", null ],
      [ "cimunit_thread_table Module", "group__cimunit__thread__table.html", null ],
      [ "CIMUnit Test Methods", "group__cimunit__user.html", null ],
      [ "cimunit_barrier Module", "group__cimunit__barrier.html", null ],
      [ "cimunit_event Module", "group__cimunit__event.html", null ],
      [ "cimunit_event_list Module", "group__cimunit__event__list.html", null ],
      [ "cimunit_event_table Module", "group__cimunit__event__table.html", null ],
      [ "cimunit_schedule Module", "group__cimunit__schedule.html", null ],
      [ "cimunit_thread Module", "group__cimunit__thread.html", null ]
    ] ],
    [ "Data Structures", "annotated.html", [
      [ "cimunit_barrier", "structcimunit__barrier.html", null ],
      [ "cimunit_event", "structcimunit__event.html", null ],
      [ "cimunit_event_list", "structcimunit__event__list.html", null ],
      [ "cimunit_event_table", "structcimunit__event__table.html", null ],
      [ "cimunit_schedule", "structcimunit__schedule.html", null ],
      [ "cimunit_thread_table", "structcimunit__thread__table.html", null ],
      [ "cimunit_thread_table_element", "structcimunit__thread__table__element.html", null ],
      [ "event_table_entry", "structevent__table__entry.html", null ]
    ] ],
    [ "Data Structure Index", "classes.html", null ],
    [ "Data Fields", "functions.html", null ],
    [ "File List", "files.html", [
      [ "cimunit.c", "cimunit_8c.html", null ],
      [ "cimunit.h", "cimunit_8h.html", null ],
      [ "cimunit_barrier.h", "cimunit__barrier_8h.html", null ],
      [ "cimunit_barrier_pthread.c", "cimunit__barrier__pthread_8c.html", null ],
      [ "cimunit_barrier_pthread.h", "cimunit__barrier__pthread_8h.html", null ],
      [ "cimunit_barrier_vxworks.c", "cimunit__barrier__vxworks_8c.html", null ],
      [ "cimunit_barrier_vxworks.h", "cimunit__barrier__vxworks_8h.html", null ],
      [ "cimunit_event.c", "cimunit__event_8c.html", null ],
      [ "cimunit_event.h", "cimunit__event_8h.html", null ],
      [ "cimunit_event_list.c", "cimunit__event__list_8c.html", null ],
      [ "cimunit_event_list.h", "cimunit__event__list_8h.html", null ],
      [ "cimunit_event_table.c", "cimunit__event__table_8c.html", null ],
      [ "cimunit_event_table.h", "cimunit__event__table_8h.html", null ],
      [ "cimunit_mutex.h", "cimunit__mutex_8h.html", null ],
      [ "cimunit_mutex_pthread.c", "cimunit__mutex__pthread_8c.html", null ],
      [ "cimunit_mutex_pthread.h", "cimunit__mutex__pthread_8h.html", null ],
      [ "cimunit_mutex_vxworks.c", "cimunit__mutex__vxworks_8c.html", null ],
      [ "cimunit_mutex_vxworks.h", "cimunit__mutex__vxworks_8h.html", null ],
      [ "cimunit_platform.h", "cimunit__platform_8h.html", null ],
      [ "cimunit_platform_darwin.h", "cimunit__platform__darwin_8h.html", null ],
      [ "cimunit_platform_linux.h", "cimunit__platform__linux_8h.html", null ],
      [ "cimunit_platform_unix_pthreads.h", "cimunit__platform__unix__pthreads_8h.html", null ],
      [ "cimunit_platform_vxworks.h", "cimunit__platform__vxworks_8h.html", null ],
      [ "cimunit_schedule.c", "cimunit__schedule_8c.html", null ],
      [ "cimunit_schedule.h", "cimunit__schedule_8h.html", null ],
      [ "cimunit_thread.h", "cimunit__thread_8h.html", null ],
      [ "cimunit_thread_pthread.c", "cimunit__thread__pthread_8c.html", null ],
      [ "cimunit_thread_pthread.h", "cimunit__thread__pthread_8h.html", null ],
      [ "cimunit_thread_table.c", "cimunit__thread__table_8c.html", null ],
      [ "cimunit_thread_table.h", "cimunit__thread__table_8h.html", null ],
      [ "cimunit_thread_vxworks.c", "cimunit__thread__vxworks_8c.html", null ],
      [ "cimunit_thread_vxworks.h", "cimunit__thread__vxworks_8h.html", null ]
    ] ],
    [ "Examples", "examples.html", [
      [ "test_example.c", "test_example_8c-example.html", null ]
    ] ],
    [ "Globals", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

