<!DOCTYPE html>






<!-- paulirish.com/2008/conditional-stylesheets-vs-css-hacks-answer-neither/ -->
<!--[if IE 8]> <html class="no-js lt-ie9" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="en"> <!--<![endif]-->

<head>
    <title>
    StepperMotor - a mercurial repository
 | mbed</title>
    <meta charset="utf-8"/>
    <meta http-equiv="X-UA-Compatible" content="IE=9; IE=8; IE=7; IE=EDGE"/><script type="text/javascript">(window.NREUM||(NREUM={})).loader_config={xpid:"VQQHVVBUGwQDUVJSBQ=="};window.NREUM||(NREUM={}),__nr_require=function(t,e,n){function r(n){if(!e[n]){var o=e[n]={exports:{}};t[n][0].call(o.exports,function(e){var o=t[n][1][e];return r(o||e)},o,o.exports)}return e[n].exports}if("function"==typeof __nr_require)return __nr_require;for(var o=0;o<n.length;o++)r(n[o]);return r}({1:[function(t,e,n){function r(t){try{c.console&&console.log(t)}catch(e){}}var o,i=t("ee"),a=t(15),c={};try{o=localStorage.getItem("__nr_flags").split(","),console&&"function"==typeof console.log&&(c.console=!0,o.indexOf("dev")!==-1&&(c.dev=!0),o.indexOf("nr_dev")!==-1&&(c.nrDev=!0))}catch(s){}c.nrDev&&i.on("internal-error",function(t){r(t.stack)}),c.dev&&i.on("fn-err",function(t,e,n){r(n.stack)}),c.dev&&(r("NR AGENT IN DEVELOPMENT MODE"),r("flags: "+a(c,function(t,e){return t}).join(", ")))},{}],2:[function(t,e,n){function r(t,e,n,r,o){try{d?d-=1:i("err",[o||new UncaughtException(t,e,n)])}catch(c){try{i("ierr",[c,(new Date).getTime(),!0])}catch(s){}}return"function"==typeof f&&f.apply(this,a(arguments))}function UncaughtException(t,e,n){this.message=t||"Uncaught error with no additional information",this.sourceURL=e,this.line=n}function o(t){i("err",[t,(new Date).getTime()])}var i=t("handle"),a=t(16),c=t("ee"),s=t("loader"),f=window.onerror,u=!1,d=0;s.features.err=!0,t(1),window.onerror=r;try{throw new Error}catch(l){"stack"in l&&(t(8),t(7),"addEventListener"in window&&t(5),s.xhrWrappable&&t(9),u=!0)}c.on("fn-start",function(t,e,n){u&&(d+=1)}),c.on("fn-err",function(t,e,n){u&&(this.thrown=!0,o(n))}),c.on("fn-end",function(){u&&!this.thrown&&d>0&&(d-=1)}),c.on("internal-error",function(t){i("ierr",[t,(new Date).getTime(),!0])})},{}],3:[function(t,e,n){t("loader").features.ins=!0},{}],4:[function(t,e,n){function r(t){}if(window.performance&&window.performance.timing&&window.performance.getEntriesByType){var o=t("ee"),i=t("handle"),a=t(8),c=t(7),s="learResourceTimings",f="addEventListener",u="resourcetimingbufferfull",d="bstResource",l="resource",p="-start",h="-end",m="fn"+p,w="fn"+h,v="bstTimer",y="pushState";t("loader").features.stn=!0,t(6);var g=NREUM.o.EV;o.on(m,function(t,e){var n=t[0];n instanceof g&&(this.bstStart=Date.now())}),o.on(w,function(t,e){var n=t[0];n instanceof g&&i("bst",[n,e,this.bstStart,Date.now()])}),a.on(m,function(t,e,n){this.bstStart=Date.now(),this.bstType=n}),a.on(w,function(t,e){i(v,[e,this.bstStart,Date.now(),this.bstType])}),c.on(m,function(){this.bstStart=Date.now()}),c.on(w,function(t,e){i(v,[e,this.bstStart,Date.now(),"requestAnimationFrame"])}),o.on(y+p,function(t){this.time=Date.now(),this.startPath=location.pathname+location.hash}),o.on(y+h,function(t){i("bstHist",[location.pathname+location.hash,this.startPath,this.time])}),f in window.performance&&(window.performance["c"+s]?window.performance[f](u,function(t){i(d,[window.performance.getEntriesByType(l)]),window.performance["c"+s]()},!1):window.performance[f]("webkit"+u,function(t){i(d,[window.performance.getEntriesByType(l)]),window.performance["webkitC"+s]()},!1)),document[f]("scroll",r,!1),document[f]("keypress",r,!1),document[f]("click",r,!1)}},{}],5:[function(t,e,n){function r(t){for(var e=t;e&&!e.hasOwnProperty(u);)e=Object.getPrototypeOf(e);e&&o(e)}function o(t){c.inPlace(t,[u,d],"-",i)}function i(t,e){return t[1]}var a=t("ee").get("events"),c=t(17)(a,!0),s=t("gos"),f=XMLHttpRequest,u="addEventListener",d="removeEventListener";e.exports=a,"getPrototypeOf"in Object?(r(document),r(window),r(f.prototype)):f.prototype.hasOwnProperty(u)&&(o(window),o(f.prototype)),a.on(u+"-start",function(t,e){var n=t[1],r=s(n,"nr@wrapped",function(){function t(){if("function"==typeof n.handleEvent)return n.handleEvent.apply(n,arguments)}var e={object:t,"function":n}[typeof n];return e?c(e,"fn-",null,e.name||"anonymous"):n});this.wrapped=t[1]=r}),a.on(d+"-start",function(t){t[1]=this.wrapped||t[1]})},{}],6:[function(t,e,n){var r=t("ee").get("history"),o=t(17)(r);e.exports=r,o.inPlace(window.history,["pushState","replaceState"],"-")},{}],7:[function(t,e,n){var r=t("ee").get("raf"),o=t(17)(r),i="equestAnimationFrame";e.exports=r,o.inPlace(window,["r"+i,"mozR"+i,"webkitR"+i,"msR"+i],"raf-"),r.on("raf-start",function(t){t[0]=o(t[0],"fn-")})},{}],8:[function(t,e,n){function r(t,e,n){t[0]=a(t[0],"fn-",null,n)}function o(t,e,n){this.method=n,this.timerDuration="number"==typeof t[1]?t[1]:0,t[0]=a(t[0],"fn-",this,n)}var i=t("ee").get("timer"),a=t(17)(i),c="setTimeout",s="setInterval",f="clearTimeout",u="-start",d="-";e.exports=i,a.inPlace(window,[c,"setImmediate"],c+d),a.inPlace(window,[s],s+d),a.inPlace(window,[f,"clearImmediate"],f+d),i.on(s+u,r),i.on(c+u,o)},{}],9:[function(t,e,n){function r(t,e){d.inPlace(e,["onreadystatechange"],"fn-",c)}function o(){var t=this,e=u.context(t);t.readyState>3&&!e.resolved&&(e.resolved=!0,u.emit("xhr-resolved",[],t)),d.inPlace(t,w,"fn-",c)}function i(t){v.push(t),h&&(g=-g,b.data=g)}function a(){for(var t=0;t<v.length;t++)r([],v[t]);v.length&&(v=[])}function c(t,e){return e}function s(t,e){for(var n in t)e[n]=t[n];return e}t(5);var f=t("ee"),u=f.get("xhr"),d=t(17)(u),l=NREUM.o,p=l.XHR,h=l.MO,m="readystatechange",w=["onload","onerror","onabort","onloadstart","onloadend","onprogress","ontimeout"],v=[];e.exports=u;var y=window.XMLHttpRequest=function(t){var e=new p(t);try{u.emit("new-xhr",[e],e),e.addEventListener(m,o,!1)}catch(n){try{u.emit("internal-error",[n])}catch(r){}}return e};if(s(p,y),y.prototype=p.prototype,d.inPlace(y.prototype,["open","send"],"-xhr-",c),u.on("send-xhr-start",function(t,e){r(t,e),i(e)}),u.on("open-xhr-start",r),h){var g=1,b=document.createTextNode(g);new h(a).observe(b,{characterData:!0})}else f.on("fn-end",function(t){t[0]&&t[0].type===m||a()})},{}],10:[function(t,e,n){function r(t){var e=this.params,n=this.metrics;if(!this.ended){this.ended=!0;for(var r=0;r<d;r++)t.removeEventListener(u[r],this.listener,!1);if(!e.aborted){if(n.duration=(new Date).getTime()-this.startTime,4===t.readyState){e.status=t.status;var i=o(t,this.lastSize);if(i&&(n.rxSize=i),this.sameOrigin){var a=t.getResponseHeader("X-NewRelic-App-Data");a&&(e.cat=a.split(", ").pop())}}else e.status=0;n.cbTime=this.cbTime,f.emit("xhr-done",[t],t),c("xhr",[e,n,this.startTime])}}}function o(t,e){var n=t.responseType;if("json"===n&&null!==e)return e;var r="arraybuffer"===n||"blob"===n||"json"===n?t.response:t.responseText;return h(r)}function i(t,e){var n=s(e),r=t.params;r.host=n.hostname+":"+n.port,r.pathname=n.pathname,t.sameOrigin=n.sameOrigin}var a=t("loader");if(a.xhrWrappable){var c=t("handle"),s=t(11),f=t("ee"),u=["load","error","abort","timeout"],d=u.length,l=t("id"),p=t(14),h=t(13),m=window.XMLHttpRequest;a.features.xhr=!0,t(9),f.on("new-xhr",function(t){var e=this;e.totalCbs=0,e.called=0,e.cbTime=0,e.end=r,e.ended=!1,e.xhrGuids={},e.lastSize=null,p&&(p>34||p<10)||window.opera||t.addEventListener("progress",function(t){e.lastSize=t.loaded},!1)}),f.on("open-xhr-start",function(t){this.params={method:t[0]},i(this,t[1]),this.metrics={}}),f.on("open-xhr-end",function(t,e){"loader_config"in NREUM&&"xpid"in NREUM.loader_config&&this.sameOrigin&&e.setRequestHeader("X-NewRelic-ID",NREUM.loader_config.xpid)}),f.on("send-xhr-start",function(t,e){var n=this.metrics,r=t[0],o=this;if(n&&r){var i=h(r);i&&(n.txSize=i)}this.startTime=(new Date).getTime(),this.listener=function(t){try{"abort"===t.type&&(o.params.aborted=!0),("load"!==t.type||o.called===o.totalCbs&&(o.onloadCalled||"function"!=typeof e.onload))&&o.end(e)}catch(n){try{f.emit("internal-error",[n])}catch(r){}}};for(var a=0;a<d;a++)e.addEventListener(u[a],this.listener,!1)}),f.on("xhr-cb-time",function(t,e,n){this.cbTime+=t,e?this.onloadCalled=!0:this.called+=1,this.called!==this.totalCbs||!this.onloadCalled&&"function"==typeof n.onload||this.end(n)}),f.on("xhr-load-added",function(t,e){var n=""+l(t)+!!e;this.xhrGuids&&!this.xhrGuids[n]&&(this.xhrGuids[n]=!0,this.totalCbs+=1)}),f.on("xhr-load-removed",function(t,e){var n=""+l(t)+!!e;this.xhrGuids&&this.xhrGuids[n]&&(delete this.xhrGuids[n],this.totalCbs-=1)}),f.on("addEventListener-end",function(t,e){e instanceof m&&"load"===t[0]&&f.emit("xhr-load-added",[t[1],t[2]],e)}),f.on("removeEventListener-end",function(t,e){e instanceof m&&"load"===t[0]&&f.emit("xhr-load-removed",[t[1],t[2]],e)}),f.on("fn-start",function(t,e,n){e instanceof m&&("onload"===n&&(this.onload=!0),("load"===(t[0]&&t[0].type)||this.onload)&&(this.xhrCbStart=(new Date).getTime()))}),f.on("fn-end",function(t,e){this.xhrCbStart&&f.emit("xhr-cb-time",[(new Date).getTime()-this.xhrCbStart,this.onload,e],e)})}},{}],11:[function(t,e,n){e.exports=function(t){var e=document.createElement("a"),n=window.location,r={};e.href=t,r.port=e.port;var o=e.href.split("://");!r.port&&o[1]&&(r.port=o[1].split("/")[0].split("@").pop().split(":")[1]),r.port&&"0"!==r.port||(r.port="https"===o[0]?"443":"80"),r.hostname=e.hostname||n.hostname,r.pathname=e.pathname,r.protocol=o[0],"/"!==r.pathname.charAt(0)&&(r.pathname="/"+r.pathname);var i=!e.protocol||":"===e.protocol||e.protocol===n.protocol,a=e.hostname===document.domain&&e.port===n.port;return r.sameOrigin=i&&(!e.hostname||a),r}},{}],12:[function(t,e,n){function r(){}function o(t,e,n){return function(){return i(t,[(new Date).getTime()].concat(c(arguments)),e?null:this,n),e?void 0:this}}var i=t("handle"),a=t(15),c=t(16),s=t("ee").get("tracer"),f=NREUM;"undefined"==typeof window.newrelic&&(newrelic=f);var u=["setPageViewName","setCustomAttribute","setErrorHandler","finished","addToTrace","inlineHit"],d="api-",l=d+"ixn-";a(u,function(t,e){f[e]=o(d+e,!0,"api")}),f.addPageAction=o(d+"addPageAction",!0),f.setCurrentRouteName=o(d+"routeName",!0),e.exports=newrelic,f.interaction=function(){return(new r).get()};var p=r.prototype={createTracer:function(t,e){var n={},r=this,o="function"==typeof e;return i(l+"tracer",[Date.now(),t,n],r),function(){if(s.emit((o?"":"no-")+"fn-start",[Date.now(),r,o],n),o)try{return e.apply(this,arguments)}finally{s.emit("fn-end",[Date.now()],n)}}}};a("setName,setAttribute,save,ignore,onEnd,getContext,end,get".split(","),function(t,e){p[e]=o(l+e)}),newrelic.noticeError=function(t){"string"==typeof t&&(t=new Error(t)),i("err",[t,(new Date).getTime()])}},{}],13:[function(t,e,n){e.exports=function(t){if("string"==typeof t&&t.length)return t.length;if("object"==typeof t){if("undefined"!=typeof ArrayBuffer&&t instanceof ArrayBuffer&&t.byteLength)return t.byteLength;if("undefined"!=typeof Blob&&t instanceof Blob&&t.size)return t.size;if(!("undefined"!=typeof FormData&&t instanceof FormData))try{return JSON.stringify(t).length}catch(e){return}}}},{}],14:[function(t,e,n){var r=0,o=navigator.userAgent.match(/Firefox[\/\s](\d+\.\d+)/);o&&(r=+o[1]),e.exports=r},{}],15:[function(t,e,n){function r(t,e){var n=[],r="",i=0;for(r in t)o.call(t,r)&&(n[i]=e(r,t[r]),i+=1);return n}var o=Object.prototype.hasOwnProperty;e.exports=r},{}],16:[function(t,e,n){function r(t,e,n){e||(e=0),"undefined"==typeof n&&(n=t?t.length:0);for(var r=-1,o=n-e||0,i=Array(o<0?0:o);++r<o;)i[r]=t[e+r];return i}e.exports=r},{}],17:[function(t,e,n){function r(t){return!(t&&t instanceof Function&&t.apply&&!t[a])}var o=t("ee"),i=t(16),a="nr@original",c=Object.prototype.hasOwnProperty,s=!1;e.exports=function(t,e){function n(t,e,n,o){function nrWrapper(){var r,a,c,s;try{a=this,r=i(arguments),c="function"==typeof n?n(r,a):n||{}}catch(f){l([f,"",[r,a,o],c])}u(e+"start",[r,a,o],c);try{return s=t.apply(a,r)}catch(d){throw u(e+"err",[r,a,d],c),d}finally{u(e+"end",[r,a,s],c)}}return r(t)?t:(e||(e=""),nrWrapper[a]=t,d(t,nrWrapper),nrWrapper)}function f(t,e,o,i){o||(o="");var a,c,s,f="-"===o.charAt(0);for(s=0;s<e.length;s++)c=e[s],a=t[c],r(a)||(t[c]=n(a,f?c+o:o,i,c))}function u(n,r,o){if(!s||e){var i=s;s=!0;try{t.emit(n,r,o)}catch(a){l([a,n,r,o])}s=i}}function d(t,e){if(Object.defineProperty&&Object.keys)try{var n=Object.keys(t);return n.forEach(function(n){Object.defineProperty(e,n,{get:function(){return t[n]},set:function(e){return t[n]=e,e}})}),e}catch(r){l([r])}for(var o in t)c.call(t,o)&&(e[o]=t[o]);return e}function l(e){try{t.emit("internal-error",e)}catch(n){}}return t||(t=o),n.inPlace=f,n.flag=a,n}},{}],ee:[function(t,e,n){function r(){}function o(t){function e(t){return t&&t instanceof r?t:t?s(t,c,i):i()}function n(n,r,o){if(!l.aborted){t&&t(n,r,o);for(var i=e(o),a=h(n),c=a.length,s=0;s<c;s++)a[s].apply(i,r);var f=u[y[n]];return f&&f.push([g,n,r,i]),i}}function p(t,e){v[t]=h(t).concat(e)}function h(t){return v[t]||[]}function m(t){return d[t]=d[t]||o(n)}function w(t,e){f(t,function(t,n){e=e||"feature",y[n]=e,e in u||(u[e]=[])})}var v={},y={},g={on:p,emit:n,get:m,listeners:h,context:e,buffer:w,abort:a,aborted:!1};return g}function i(){return new r}function a(){(u.api||u.feature)&&(l.aborted=!0,u=l.backlog={})}var c="nr@context",s=t("gos"),f=t(15),u={},d={},l=e.exports=o();l.backlog=u},{}],gos:[function(t,e,n){function r(t,e,n){if(o.call(t,e))return t[e];var r=n();if(Object.defineProperty&&Object.keys)try{return Object.defineProperty(t,e,{value:r,writable:!0,enumerable:!1}),r}catch(i){}return t[e]=r,r}var o=Object.prototype.hasOwnProperty;e.exports=r},{}],handle:[function(t,e,n){function r(t,e,n,r){o.buffer([t],r),o.emit(t,e,n)}var o=t("ee").get("handle");e.exports=r,r.ee=o},{}],id:[function(t,e,n){function r(t){var e=typeof t;return!t||"object"!==e&&"function"!==e?-1:t===window?0:a(t,i,function(){return o++})}var o=1,i="nr@id",a=t("gos");e.exports=r},{}],loader:[function(t,e,n){function r(){if(!b++){var t=g.info=NREUM.info,e=d.getElementsByTagName("script")[0];if(setTimeout(f.abort,3e4),!(t&&t.licenseKey&&t.applicationID&&e))return f.abort();s(v,function(e,n){t[e]||(t[e]=n)}),c("mark",["onload",a()],null,"api");var n=d.createElement("script");n.src="https://"+t.agent,e.parentNode.insertBefore(n,e)}}function o(){"complete"===d.readyState&&i()}function i(){c("mark",["domContent",a()],null,"api")}function a(){return(new Date).getTime()}var c=t("handle"),s=t(15),f=t("ee"),u=window,d=u.document,l="addEventListener",p="attachEvent",h=u.XMLHttpRequest,m=h&&h.prototype;NREUM.o={ST:setTimeout,CT:clearTimeout,XHR:h,REQ:u.Request,EV:u.Event,PR:u.Promise,MO:u.MutationObserver},t(12);var w=""+location,v={beacon:"bam.nr-data.net",errorBeacon:"bam.nr-data.net",agent:"js-agent.newrelic.com/nr-998.min.js"},y=h&&m&&m[l]&&!/CriOS/.test(navigator.userAgent),g=e.exports={offset:a(),origin:w,features:{},xhrWrappable:y};d[l]?(d[l]("DOMContentLoaded",i,!1),u[l]("load",r,!1)):(d[p]("onreadystatechange",o),u[p]("onload",r)),c("mark",["firstbyte",a()],null,"api");var b=0},{}]},{},["loader",2,10,4,3]);</script><script type="text/javascript">window.NREUM||(NREUM={});NREUM.info={"beacon":"bam.nr-data.net","queueTime":1,"licenseKey":"0c341c3bde","agent":"","transactionName":"Z11UMERTXUUEWhYLXV4XcBFYUUdfCldND1BVXBgWU0JcRQxNDRBbVUsYEl9XREVfSwcSXW9cUxBXW18=","applicationID":"735302,5266396","errorBeacon":"bam.nr-data.net","applicationTime":351}</script>
    <!-- Set the viewport width to device width for mobile -->
    <meta name="viewport" content="user-scalable=yes,width=device-width,initial-scale=0.9"/>

    

    <!-- Included CSS Files -->
    <link type="text/css" href="/static/A.css,,_app.css+css,,_mbed.css+css,,_questions.css+css,,_responsive-tables.css+webfonts,,_ss-standard.css+css,,_general_foundicons.css+css,,_social_foundicons.css+css,,_import-button.css,Mcc.6hweedjXFh.css.pagespeed.cf.rXFMLDXdww.css" rel="stylesheet"/>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css">
    <link rel="stylesheet" type="text/css" href="https://fonts.googleapis.com/css?family=Open+Sans:400italic,400,600italic,600,700italic,700,800italic,800">

    <script src="/static/js/foundation/modernizr.foundation.js.pagespeed.jm.fHFG8H195u.js"></script>
<script src="/static/js/foundation/jquery.js.pagespeed.jm.HblgdAtz3p.js"></script>
<script src="/static/js/date.js+mbedcom.js+import-button.js+jquery.timeago.js.pagespeed.jc.TqouplBntB.js"></script><script>eval(mod_pagespeed_Ofw5$xybCR);</script>
<script>eval(mod_pagespeed_WKG7Pme_wq);</script>
<script>eval(mod_pagespeed_IV8teJ1Egd);</script>
<script>eval(mod_pagespeed_5dtSPSSlBV);</script>
<script src="/static/js/jquery.cycle.all.latest.js+json2.js+foundation,_jquery.event.move.js+foundation,_jquery.event.swipe.js+foundation,_jquery.foundation.alerts.js+foundation,_jquery.foundation.buttons.js.pagespeed.jc.naBCxJraGa.js"></script><script>eval(mod_pagespeed_sgzDt0TR$s);</script>
<script>eval(mod_pagespeed_SZ_1k$2DaU);</script>
<script>eval(mod_pagespeed_dLrHXePpSz);</script>
<script>eval(mod_pagespeed_i2SP3Stp1X);</script>
<script>eval(mod_pagespeed_567YJB4z3s);</script>
<script>eval(mod_pagespeed_UxfahZVCG4);</script>
<script src="/static/js,_foundation,_jquery.foundation.forms.js+js,_foundation,_jquery.foundation.navigation.js+js,_foundation,_jquery.foundation.tabs.js+js,_foundation,_jquery.foundation.reveal.js+js,_foundation,_jquery.foundation.topbar.js+js,_foundation,_jquery.placeholder.js+js,_foundation,_responsive-tables.js+js,_jquery.smooth-scroll.min.js+webfonts,_ss-standard.js+webfonts,_ss-social.js+js,_foundation,_app.js+js,_clipboard.min.js.pagespeed.jc.vSuBcDawgV.js"></script><script>eval(mod_pagespeed_AYmLeGe3xm);</script>
<script>eval(mod_pagespeed_a2gdlseRvJ);</script>
<script>eval(mod_pagespeed_pHsAO6E8d4);</script>
<script>eval(mod_pagespeed_zuece6P4An);</script>
<script>eval(mod_pagespeed_dAoq3OW7vY);</script>
<script>eval(mod_pagespeed_WznPWbuyz_);</script>
<script>eval(mod_pagespeed_9AuvBNBptM);</script>
<script>eval(mod_pagespeed__yzEbVRriU);</script>
<script>eval(mod_pagespeed_yHz83s_fwC);</script>
<script>eval(mod_pagespeed_p5p2wzu3Cx);</script>
<script>eval(mod_pagespeed_fBYX5Lh9yl);</script>
<script>eval(mod_pagespeed_Jm6w4rK357);</script>

    
    
<!--[if IE]><script type="text/javascript" src="/static/js/excanvas.js"></script><![endif]-->
  <style>.page-header{margin-bottom:2em}dt{width:15em;padding:.2em;float:left;margin:0;font-weight:bold;clear:left}dd{margin-left:16em;padding:.2em}table#changes_list{table-layout:fixed}.description{background-color:#feffaa;color:#000;padding:1em;margin:0}span.desc{padding-right:1em}span.logtags span{padding:0 6px;font-weight:normal;font-size:11px;border:1px solid;background-color:#faf;border-color:#fcf #f0e #f0e #fcf}span.logtags span.tagtag{background-color:#ffa;border-color:#ffc #fe0 #fe0 #ffc}span.logtags span.branchtag{background-color:#afa;border-color:#cfc #0c3 #0c3 #cfc}span.logtags span.inbranchtag{background-color:#d5dde6;border-color:#e3ecf4 #9398f4 #9398f4 #e3ecf4}div.diff pre{margin:10px 0 0 0!important}div.diff pre span{font-family:monospace;white-space:pre;font-size:1.2em;padding:3px 0!important}td.source{white-space:pre;font-family:monospace}div.source{font-size:1.2em}.linenr{color:#999;text-align:right}.lineno{text-align:right}.lineno a{color:#999}td.linenr{width:10px}div#powered-by{position:absolute;width:75px;top:15px;right:20px;font-size:1.2em}div#powered-by a{color:#eee;text-decoration:none}div#powered-by a:hover{text-decoration:underline}p.files{margin:0 0 0 20px;font-size:2.0em;font-weight:bold}div#wrapper{position:relative}canvas{position:absolute;z-index:5;top:-.7em}ul#nodebgs li.parity0{background:#f1f6f7}ul#nodebgs li.parity1{background:#fff}ul#graphnodes{position:absolute;z-index:10;top:7px;padding:0 0 0 1em;margin:0;list-style:none inside none}ul#nodebgs li,ul#graphnodes li{list-style:none inside none!important}ul#nodebgs{list-style:none inside none!important;padding:0}ul#graphnodes li,ul#nodebgs li{height:39px}.object-tools ul{}.object-tools li{border-bottom:1px solid #ddd;float:right;padding-left:1em;list-style:none}</style>

</head>

<body>
    
<style>body{font-family:"Open Sans",Arial,sans-serif}.common-top-bar .dropdown,.sub-bar .dropdown{border:none;box-shadow:0 5px 3px 1px rgba(0,0,0,.3);top:100%;left:0!important}.common-top-bar{padding:0 .5em;min-height:60px}.common-top-bar .columns{padding-left:0}.common-top-bar{background:#fff}.common-top-bar ul li{border-top:5px solid #fff}.common-top-bar ul li a{font-size:.9em;color:#7a7a7a;font-weight:400;margin:.6rem 0;padding:.1rem .8rem}.common-top-bar ul li.logo a{padding-left:.1rem}.common-top-bar .menu li a img.logo{min-width:50px!important;height:24px;width:168px;margin-bottom:5px}.common-top-bar .search .button{border:none;background:none;border-color:none;color:#7a7a7a;position:absolute;top:2px;right:0}.common-top-bar .search form{position:relative;padding:0 0;width:100%!important}.common-top-bar .search form,.common-top-bar .search form input{width:100%;max-width:100%;height:40px}.common-top-bar input{margin:10px .3em 10px 0;max-width:auto;top:0}.common-top-bar ul li.selected{border-top:5px solid #fff}.common-top-bar ul li.dev.selected{border-top:5px solid #00c3dc}.common-top-bar ul li.partners.selected{border-top:5px solid #8a6eaf}.menu>li{display:table-cell}.menu{padding-left:0}.common-top-bar ul li.selected a:link,.off-canvas-wrap{background:#fff}.sub-bar{background-color:#0a7084}.sub-bar a{color:#fff;font-size:.9em}.has-dropdown .dropdown a{color:#7a7a7a}.sub-bar .row{margin:0 auto}.sub-bar.mbedcom .row{max-width:62.5rem}.sub-bar.dev .row{max-width:100%;width:1200px}.sub-bar.dev{display:none;background:#128cab}.sub-bar.partners{display:none;background:#6a4e93}.sub-bar.partners .row{}.sub-bar ul li{padding:.8rem 0}.sub-bar ul li a{padding:.2em 1em .2em 1em}.sub-bar .user-links{padding:.4rem 0}.sub-bar .user-links a{padding:.6em 1em;background:rgba(0,195,220,1);font-weight:600;margin-right:1rem;margin-left:1rem}.sub-bar .user-links a:hover{background:rgba(0,195,220,.5)}.sub-bar .dropdown{padding:.3rem}.sub-bar .dropdown li{padding:.2rem 0}.language .dropdown a{border:none}.menu .active a{background:#fff}ul.menu{margin-left:0}.dropdown.menu li.is-dropdown-submenu-parent a::after{border:#fff}ul.menu li.has-dropdown ul.dropdown li a{background-image:none;display:block;line-height:1.4em;padding:5px 10px}ul.menu li a .fa{margin-left:8px}iframe{height:100%}::-webkit-input-placeholder{color:rgba(20,20,20,.4)}:-moz-placeholder{color:rgba(20,20,20,.4);opacity:1}::-moz-placeholder{color:rgba(20,20,20,.4);opacity:1}:-ms-input-placeholder{color:rgba(20,20,20,.4)}@media screen and (min-width:40em) and (max-width:63.9375em){.sub-bar.dev ul li a{padding-left:.3rem;padding-right:.3rem}.sub-bar.dev ul li.user-links a{padding-left:1rem;padding-right:1rem}.sub-bar.dev ul li.home a{background:blue1}}@media screen and (max-width:39.9375em){.common-common-top-bar .nav,.common-common-top-bar .search{padding-left:0;padding-right:0}.common-common-top-bar ul li.logo a{padding-left:0}.nav.columns{height:50px}.common-top-bar{height:115px}.sub-bar ul li{padding:.8rem 0}.sub-bar ul li a.menutrigger{margin-left:-.8em}.sub-bar ul li.home a{padding:.2em .8em .2em .3em;border-right:2px dotted rgba(255,255,255,.3)}.sub-bar ul li a{padding:.2em .5em .2em .5em}.sub-bar ul li.is-accordion-submenu-parent a{padding-left:2.1rem}.sub-bar ul li.is-accordion-submenu-parent a::after{border-color:#fff transparent transparent;left:.8rem;top:55%}.sub-bar ul.sub-menu .menu.vertical.nested{background:red}.sub-bar ul.sub-menu{margin-top:.5rem}.sub-bar ul.sub-menu li{padding-top:.5rem;padding-bottom:.5rem}.sub-bar ul.sub-menu li a{font-weight:600}.sub-bar ul.sub-menu li ul a{font-weight:300}.sub-bar ul.sub-menu li ul li{padding-top:.3rem;padding-bottom:.3rem}.sub-bar .language .dropdown{left:inherit!important;right:0!important}}</style>
<div class="common-top-bar top-bar">
    <div class="nav small-12 medium-9 columns">
        <ul class="menu" data-dropdown-menu="t822t7-dropdown-menu" role="menubar">
            <li class="mbedcom logo " role="menuitem">
                <a title="back to mbed home" href="https://mbed.com" tabindex="0">
                    <script data-pagespeed-no-defer>//<![CDATA[
(function(){var g=this;function h(b,d){var a=b.split("."),c=g;a[0]in c||!c.execScript||c.execScript("var "+a[0]);for(var e;a.length&&(e=a.shift());)a.length||void 0===d?c[e]?c=c[e]:c=c[e]={}:c[e]=d};function l(b){var d=b.length;if(0<d){for(var a=Array(d),c=0;c<d;c++)a[c]=b[c];return a}return[]};function m(b){var d=window;if(d.addEventListener)d.addEventListener("load",b,!1);else if(d.attachEvent)d.attachEvent("onload",b);else{var a=d.onload;d.onload=function(){b.call(this);a&&a.call(this)}}};var n;function p(b,d,a,c,e){this.h=b;this.j=d;this.l=a;this.f=e;this.g={height:window.innerHeight||document.documentElement.clientHeight||document.body.clientHeight,width:window.innerWidth||document.documentElement.clientWidth||document.body.clientWidth};this.i=c;this.b={};this.a=[];this.c={}}function q(b,d){var a,c,e=d.getAttribute("data-pagespeed-url-hash");if(a=e&&!(e in b.c))if(0>=d.offsetWidth&&0>=d.offsetHeight)a=!1;else{c=d.getBoundingClientRect();var f=document.body;a=c.top+("pageYOffset"in window?window.pageYOffset:(document.documentElement||f.parentNode||f).scrollTop);c=c.left+("pageXOffset"in window?window.pageXOffset:(document.documentElement||f.parentNode||f).scrollLeft);f=a.toString()+","+c;b.b.hasOwnProperty(f)?a=!1:(b.b[f]=!0,a=a<=b.g.height&&c<=b.g.width)}a&&(b.a.push(e),b.c[e]=!0)}p.prototype.checkImageForCriticality=function(b){b.getBoundingClientRect&&q(this,b)};h("pagespeed.CriticalImages.checkImageForCriticality",function(b){n.checkImageForCriticality(b)});h("pagespeed.CriticalImages.checkCriticalImages",function(){r(n)});function r(b){b.b={};for(var d=["IMG","INPUT"],a=[],c=0;c<d.length;++c)a=a.concat(l(document.getElementsByTagName(d[c])));if(0!=a.length&&a[0].getBoundingClientRect){for(c=0;d=a[c];++c)q(b,d);a="oh="+b.l;b.f&&(a+="&n="+b.f);if(d=0!=b.a.length)for(a+="&ci="+encodeURIComponent(b.a[0]),c=1;c<b.a.length;++c){var e=","+encodeURIComponent(b.a[c]);131072>=a.length+e.length&&(a+=e)}b.i&&(e="&rd="+encodeURIComponent(JSON.stringify(t())),131072>=a.length+e.length&&(a+=e),d=!0);u=a;if(d){c=b.h;b=b.j;var f;if(window.XMLHttpRequest)f=new XMLHttpRequest;else if(window.ActiveXObject)try{f=new ActiveXObject("Msxml2.XMLHTTP")}catch(k){try{f=new ActiveXObject("Microsoft.XMLHTTP")}catch(v){}}f&&(f.open("POST",c+(-1==c.indexOf("?")?"?":"&")+"url="+encodeURIComponent(b)),f.setRequestHeader("Content-Type","application/x-www-form-urlencoded"),f.send(a))}}}function t(){var b={},d=document.getElementsByTagName("IMG");if(0==d.length)return{};var a=d[0];if(!("naturalWidth"in a&&"naturalHeight"in a))return{};for(var c=0;a=d[c];++c){var e=a.getAttribute("data-pagespeed-url-hash");e&&(!(e in b)&&0<a.width&&0<a.height&&0<a.naturalWidth&&0<a.naturalHeight||e in b&&a.width>=b[e].o&&a.height>=b[e].m)&&(b[e]={rw:a.width,rh:a.height,ow:a.naturalWidth,oh:a.naturalHeight})}return b}var u="";h("pagespeed.CriticalImages.getBeaconData",function(){return u});h("pagespeed.CriticalImages.Run",function(b,d,a,c,e,f){var k=new p(b,d,a,e,f);n=k;c&&m(function(){window.setTimeout(function(){r(k)},0)})});})();pagespeed.CriticalImages.Run('/mod_pagespeed_beacon','http://developer.mbed.org/users/melse/code/StepperMotor/file/52fb09e87581/Stepper.cpp','QOs6thfRpi',true,false,'dMk59LcpR2o');
//]]></script><img src="https://www.mbed.com/static/img/ARMmbedLogo.svg" alt="" class="logo" data-pagespeed-url-hash="2453606674" onload="pagespeed.CriticalImages.checkImageForCriticality(this);">
                </a>
            </li>
            <li class="dev selected" role="menuitem">
                <a href="https://developer.mbed.org">
                    Developer <span class="hide-for-small-only">Resources</span>
                </a>
            </li>
            <li class="partners " role="menuitem">
                <a href="https://partners.mbed.com">Partners</a>
            </li>
        </ul>
    </div>
    <div class="search small-12 medium-3 medium three columns">
        <form class="search float-right" action="https://developer.mbed.org/search/" method="GET">
            <input type="search" name="q" placeholder="Search mbed...">
            <button type="submit button" class="button"><i class="general fa fa-search"></i></button>
        </form>
    </div>
</div>

    <div class="nav-wrapper hide-on-print">
        <div class="row">
            <div class="twelve columns navigation">
            

                <ul class="nav-bar menu-list" id="nav">

                    <li class="hasdropdown not-click">
                        <a href="#">
                            Hardware
                        </a>
                        <ul class="dropdown no-bullet">
                            <li><a href="/platforms">Boards</a></li>
                            <li><a href="/components/">Components</a></li>
                        </ul>
                    </li>
                    <li class="hasdropdown not-click">
                        <a href="#">
                            Documentation
                        </a>
                        <ul class="dropdown no-bullet">
                            <li><a href="https://docs.mbed.com/">Documentation</a></li>
                            <li><a href="/cookbook/">Cookbook</a></li>
                        </ul>
                    </li>
                    <li><a href="/code/">Code</a></li>
                    <li><a href="/questions/">Questions</a></li>
                    <li><a href="/forum/">Forum</a></li>
                    <li class="navSpacer">|</li>
                    
                    <li><a href="/account/login/?next=/users/melse/code/StepperMotor/file/52fb09e87581/Stepper.cpp">Log In/Signup</a></li>
                     
                    <li class="user-links"><a href="/compiler/" target="_blank">Compiler</a></li>

                </ul>
            
            </div>
        </div>
    </div>

    <div class="blue">
        <div class="row" id="top">
            <div class="six columns">
                <div class="breadcrumbs">
                    
    
    <a href="/activity/">Users</a> &raquo; <a href="/users/melse/">melse</a>
    
    
 
        &raquo; <a href="/users/melse/code/">Code</a>

        
        &raquo; <a href="/users/melse/code/StepperMotor/">StepperMotor</a>


                </div>
            </div>
            <div class="six columns header search-block">
                
                
            </div>
        </div><!-- end of #top -->

        
    </div>

    
<div class="row">
    <div class="nine columns main-content" id="mbed-content">
        

        







<div class="content-actions"></div>




<div style="font-size: 1.6em; padding-bottom: 4px;">
    
        <a href="/users/melse/">
            
                <img src="data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/2wBDAAUDBAQEAwUEBAQFBQUGBwwIBwcHBw8LCwkMEQ8SEhEPERETFhwXExQaFRERGCEYGh0dHx8fExciJCIeJBweHx7/2wBDAQUFBQcGBw4ICA4eFBEUHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh7/wAARCAAyADIDASIAAhEBAxEB/8QAGwAAAgMBAQEAAAAAAAAAAAAAAAYEBwgFAwH/xAAzEAABAwMCBAQEBAcAAAAAAAABAgMEAAURBiESEzFBByJRYRQVMnEII4GRGCRCUmKh4f/EABkBAAMBAQEAAAAAAAAAAAAAAAIDBAUBAP/EAB4RAAMAAgMBAQEAAAAAAAAAAAABAgMRBBIhMVEU/9oADAMBAAIRAxEAPwDnazsd30ywt6JbEybVHd5jZQouAgjr/wB9alaP1ta0WdbdwRI4W1ozw8KVtJWCFfVspGAcp369KiaEkX+w2Kfd5ba2LZHb43WlqylWSACkHpkmkfxN1NHvD9tnpt6YXKUtCyyscLycbAgdCCahxU96NHNiTn00LpPxrFtYTFbHzCIkYSXXMFsdsdSBjscgdsDarX0J4g2zVDioYQIs0AkN8wKSr7H174NYX0rGvF7ntxbQ2nmYByDhKRj+pXb9a0Dpy6RfDvSXOcLM2e2Oa84FYSFD/I9AMdf2przua+iP41U+I0eUuhR3z6j1oGU7qOc9KQ9B+IkG+2yPKuLot5kI4kOuAoaWe+FK6du++ackrKHClw4ydvar5pUtoyrhy9MkcaaK8Mo/u/3RRA+GTrvrM3QT9H3WxuRkzByS+XQs42PEcAADIG1UB4hxXLRq5Fp54caabStBySPN9/tT0zdb9MRIN4ZiM/Do4/iWXAoL79uh77gUrXrTzl708zrVUl0Ovy1MOJUnI5Q8qFD03BB+46d8zjw03+G/zc8Y+qr63pDTAvblt04IUMvsE7rMfZx3OMDi601aPZuVubcmSw3PtchIadYeRxIWDgkbncj1B6ikHSF2biFtuWy2/wAvYKUnPSn656sTf7P8uRFylvCuUhOCoDsAO/tSL2vNFcJNdmx1uF4sNx0PLgWuype07JBiTypw8bRVgJWMncBWN+xA7VUmgvHnXugYb+nJjjF4jRlKYZE8KWuKUkghKgQVJ2+k9O2K94Nzu82HFt8G3tsRUzWnFJmp4EoQlQJ2OOvdW5xsBXr4paGZkeJlujQlOMW3U6mnGn8cRS59C04OxwSD7hVVcWnLaIufjThW0dL+I7XS/Mm52ZAO4T8INvbc0VQdwUiHPkQ/yXeQ6pvjAOFcJIyN++KKt7GZ0kc9c6tauDD0G3BCW3F/zC0JAGcfTtUyJr+5N+GatDCDEEQnIkJKg6MuBwgjODk7dBtVbW134VS1OAKbX9aD0NdlCkOALYJUlYyAeo+9BjwqfENzZe/rPSReHIz0dt1X5ZKiVAbjpufWm6x3B5Abf4coUPK4k5Sr3B6UjS7e5IVxqOSBsAK7OhbpL07cg80nnxioc+K6khLg/Xor3r18aaDx8qo++lq2kSbjIbUILknfylJxv7+1ON603q6dddJXpbsSVbrbNRIkR21eeMniHEsdlJCRkgbjHQjemPQiNOXe1RrrbYqAw9vlvylKh1SR2IPUV2glNjg3Bu3lyUiHFW8VvqA4PKSEk+g23rmLhuK2zuXlLJHVFU3Hwc0HMuEmWJL5D7qnAUvDHmJO3tvRUVq4WmQ0iQ5JiBbqQtQVywQTuc0UZFt/pnFIBeYBAIK9waYI4HoKKKbIdEodBXxBJSc7+Y0UUwWX3+FVSlW3UDalEoTIZUlJOwJQrJA98D9qsLUADum9VNOgLbVCkBSFbgjgVsRRRTV8OL6zL1uUVW+MpRJJaSSSeuwooooDx//Z" data-pagespeed-url-hash="3547532695" onload="pagespeed.CriticalImages.checkImageForCriticality(this);">

            Matthew Else
        </a> 
    
    / <a style="font-weight: bold;" href="/users/melse/code/StepperMotor/">
        
            <i title="This repository is a library" class="fa icon_library_2" aria-hidden="true"></i>
        

        StepperMotor</a>

    
</div>



    <br/>
    <p>A simple stepper motor driver library, supporting micro-stepping drivers such as the Pololu A4988 stepper driver carrier or the Sparkfun EasyDriver.</p>











   

<div class="page-header">
        <ul id="tabmenu">


            <li><a href="/users/melse/code/StepperMotor/">
              Home</a></li>


            <li><a href="/users/melse/code/StepperMotor/shortlog">
              History</a></li>


            <li><a href="/users/melse/code/StepperMotor/graph">
             Graph</a></li>


            <li><a href="/users/melse/code/StepperMotor/docs/">
              API Documentation</a></li>


            <li><a href="/users/melse/code/StepperMotor/wiki/">
              Wiki</a></li>



    
                <li><a href="/users/melse/code/StepperMotor/pull-requests/">
                  Pull Requests</a></li>
    





        </ul>
    </div>



<p>Stepper Motor Driver, designed for use with the Pololu A4988 breakout, however more than likely compatible with, for example the Sparkfun Easy Driver</p>




<div id="container">
      
        <ul class="object-tools">
            <li class="current"><a href="/users/melse/code/StepperMotor/file/52fb09e87581/Stepper.cpp">file</a></li>
            <li><a href="/users/melse/code/StepperMotor/log/52fb09e87581/Stepper.cpp">revisions</a></li>
            <li><a href="/users/melse/code/StepperMotor/annotate/52fb09e87581/Stepper.cpp">annotate</a></li>
            <li><a href="/users/melse/code/StepperMotor/diff/52fb09e87581/Stepper.cpp">diff</a></li>
            <li><a href="/users/melse/code/StepperMotor/raw-file/52fb09e87581/Stepper.cpp">raw</a></li>
        </ul>

   <div class="module">

    <h2>Stepper.cpp</h2>

    <dl class="overview ">
        <dt>Committer:</dt>
        <dd>melse</dd>
        <dt>Date:</dt>
        <dd><abbr class="timeago" title="Sun Feb 24 16:23:02 2013 +0000">2013-02-24</abbr></dd>
        
        <dt>Revision:</dt>
        <dd><b><a class="list" href="/users/melse/code/StepperMotor/rev/#node|short#">0:52fb09e87581</a></b></dd>
        
        
    </dl>

    <div class="source">
     <h3>File content as of revision 0:52fb09e87581:</h3>
        <pre class="mbed-code">
#include &quot;Stepper.h&quot;
#include &quot;mbed.h&quot;

stepper::stepper(PinName _en, PinName ms1, PinName ms2, PinName ms3, PinName _stepPin, PinName dir):en(_en),
    microstepping(ms1, ms2, ms3),
    stepPin(_stepPin),
    direction(dir)
{
}

void stepper::step(int microstep, int dir, float speed)
{
    if (microstep == 1) {
        microstepping = 0;
    } else if (microstep &lt;= 4) {
        microstepping = microstep / 2;
    } else if (microstep &gt; 4) {
        microstepping = (microstep / 2) - 1;
    }
    if (dir == 1) {
        direction = 0;
    } else if (dir == 0) {
        direction = 1;
    }
    
    //  Step...
    stepPin = 1;
    wait(1/speed);
    stepPin = 0;
    wait(1/speed);
}

void stepper::enable()
{
    en = 0;
}

void stepper::disable()
{
    en = 1;
}
            </pre>
    </div>

    </div>
</div>
            



    </div>

    <div class="three columns sidebar ">
        








<div class="panel">
    <h5 class="subheader">Repository toolbox</h5>
    <table id="repo_actions">
        <tr>
            <td>
                

<div id="import-button" class="import-button"></div>
<script type="text/javascript">new ImportButton($("#import-button"),{last_used_workspace:{type:"compiler"},compiler_import_url:"https://developer.mbed.org/compiler/#import:/users/melse/code/StepperMotor/;mode:lib",clone_url:"http://mbed.org/users/melse/code/StepperMotor/",is_library:true,c9_enabled:false,cli_enabled:true});</script>

            </td>
        </tr>
        <tr>
        	<td>
    	    	<a style="width: 100%;" class="button secondary small" href="/users/melse/code/StepperMotor/export">
    	    		<span>
    	    			<i class="fa fa-cloud-download" aria-hidden="true"></i>
    	    			Export to desktop IDE
    	    		</span>
    	    	</a>
        	</td>
        </tr>

        

        

        

        

        

    </table>
</div>


<div class="panel">
    <h5 class="subheader">Repository details</h5>
    <table>
        
        <tr>
            <th>Type:</th>
            <td>
                <i class="fa fa-cog" aria-hidden="true"></i>
                Library
            </td>
        </tr>
        
        <tr>
            <th>Created:</th>
            <td><abbr class="timeago" title="2013-02-24T16:25:22+00:00">24 Feb 2013</abbr></td>
        </tr>
        <tr>
            <th>Imports:</th>
            <td>
                <a title="Number of times this repository has been imported" href="/users/melse/code/StepperMotor/">
                    <i class="fa icon_imports" aria-hidden="true"></i>
                    173
                </a>
            </td>
        </tr>
        <tr>
            <th>Forks:</th>
            <td>
                <a title="Copies of this repository" href="/users/melse/code/StepperMotor/forks">
                    <i class="fa icon_repo_fork" aria-hidden="true"></i>
                    1
                </a>
            </td>
        </tr>
        <tr>
            <th width="40%">Commits:</th>
            <td>
                <a href="shortlog">
                    <i class="fa icon_commits" aria-hidden="true"></i>
                    1
                </a>
            </td>
        </tr>
        <tr>
            <th>Dependents:</th>
            <td>
                <a title="Programs or libraries which need this repository" href="/users/melse/code/StepperMotor/dependents">
                    <i class="fa icon_repo_depens" aria-hidden="true"></i>
                    0
                </a>
            </td>
        </tr>
        <tr>
            <th>Dependencies:</th>
            <td>
                <a title="Libraries which this program or library needs to function" href="/users/melse/code/StepperMotor/dependencies">
                    <i class="fa icon_repo_deps fa-flip-vertical" aria-hidden="true"></i>
                    0
                </a>
            </td>
        </tr>
        <tr>
            <th>Followers:</th>
            <td>
                <a title="Followers of this repository" href="/users/melse/code/StepperMotor/followers">
                    <i class="fa icon_add" aria-hidden="true"></i>
                    9
                </a>
            </td>
        </tr>
        
    </table>

    

</div>








<div class="panel">
    <h5 class="subheader">Software licencing information</h5>
    <div style="text-align: center; ">
        <img src="/static/img/xOSI.png.pagespeed.ic.GHeg6V3bGN.png" class="border" data-pagespeed-url-hash="2412592522" onload="pagespeed.CriticalImages.checkImageForCriticality(this);"/>
        <p>
            The code in this repository is <a href="http://mbed.org/handbook/Apache-Licence">Apache</a> licensed.
        </p>
    </div>
</div>







    </div>
</div>


    <div class="row footer hide-on-print">
        <div class="twelve columns">
            <hr/>
            <ul>
                <li>&copy; mbed</li>
                <li><a href="/blog">blog</a></li>
                <li><a href="/handbook/Jobs">we're hiring!</a></li>
                <li><a href="/handbook/Help">support</a></li>
                <li><a href="/handbook/Service-status">service status</a></li>
                <li><a href="/privacy">privacy policy</a></li>
                <li><a href="/terms">terms and conditions</a> </li>
            </ul>
       </div>
	</div>



<script type="text/javascript">var gaJsHost=(("https:"==document.location.protocol)?"https://ssl.":"http://www.");document.write(unescape("%3Cscript src='"+gaJsHost+"google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));</script>
<script type="text/javascript">try{var pageTracker=_gat._getTracker("UA-1447836-8");pageTracker._setCustomVar(1,'User Type','Guest',2);pageTracker._trackPageview();}catch(err){}</script>





<div id="cookiemodule">
    <div class="modouter">
        <div class="modinner">
            <h5>Important information</h5>
            <div class="modcontent">
                <div class="intro">
                    <p>This site uses cookies to store information on your computer. By continuing to use our site, you consent to our
                    <a href="/privacy/">cookies</a>.</p>
                </div>
                <div class="modopen">
                    <p><p style="margin: 0cm 0cm 0pt">ARM websites use two types of cookie: (<strong>1)</strong> those that enable the site to function and perform as required; and <b>(2)</b> analytical cookies which anonymously track visitors only while using the site. If you are not happy with this use of these cookies please review our <a target="_self" href="/privacy/">Privacy Policy</a> to learn how they can be disabled. By disabling cookies some features of the site will not work.</p></p>
                </div>
                <button class="readmore">Read More</button>
                <button class="accept" id="">accept and hide this message</button>
            </div>
        </div>
    </div>
</div>

<script type="text/javascript">jQuery(document).ready(function(){function create(name,value,days,path,domain){path=typeof path!=='undefined'?path:'/';domain=typeof domain!=='undefined'?'; domain='+domain:'';if(days){var date=new Date();date.setTime(date.getTime()+(days*24*60*60*1000));var expires="; expires="+date.toGMTString();}else{var expires="";}document.cookie=name+"="+value+expires+domain+"; path="+path;}function read(name){var nameEQ=name+"=";var ca=document.cookie.split(';');for(var i=0;i<ca.length;i++){var c=ca[i];while(c.charAt(0)==' ')c=c.substring(1,c.length);if(c.indexOf(nameEQ)==0)return c.substring(nameEQ.length,c.length);}return null;}function erase(name){create(name,"",-1);}create('testCookies','yes',365,'/','.mbed.org');if(read("testCookies")=='yes'&&read("acceptCookies")!='yes'){jQuery('#cookiemodule').css('display','block');jQuery('button.readmore').click(function(){jQuery('.modopen').slideToggle('slow');if(jQuery(this).text()=="Read More"){jQuery(this).text("Read Less");}else{jQuery(this).text("Read More");};});jQuery('button.accept').click(function(){create('acceptCookies','yes',365,'/','.mbed.org');jQuery('#cookiemodule').fadeOut('slow');});jQuery('button.close').click(function(){jQuery('#cookiemodule').fadeOut('slow');});}});</script>


<div id="flag-content" class="reveal-modal small">
    <h2>Report Content</h2>
    <a class="close-reveal-modal">&#215;</a>
    <form action="" method="post" id="flag-content-form">
        <input type='hidden' name='csrfmiddlewaretoken' value='3VFX9y1GvBYhnNVdr8S9lRAZrmf7BRlA'/>
        <ul>
            <li>
                <label for="id_reason_1">
                    <input id="id_reason_1" name="reason" type="radio" value="1"/>
                    Spam
                </label>
            </li>
            <li>
                <label for="id_reason_2">
                    <input id="id_reason_2" name="reason" type="radio" value="2"/>
                    Inappropriate
                </label>
            </li>
        </ul>
        <a class="button secondary cancel-flag">Cancel</a>
        <input type="submit" value="Report" class="button"/>
    </form>
</div>

<div id="access-warning-modal" class="reveal-modal">
    <h2>Access Warning</h2>
    <p>You do not have the correct permissions to perform this operation. Please, contact us at support@mbed.com to gain full access.</p>
    <a class="close-reveal-modal">&#215;</a>
</div>

</body>
</html>

