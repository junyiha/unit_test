import{_ as s,r as e,a as i,o as a,c as o,w as t,b as n,d as l,e as E,f as h,u as c,g as d,h as g,p as r,i as R}from"./index.c2040b64.js";import p from"./index.ac20c68d.js";const v=s=>(r("data-v-cd1e7f63"),s=s(),R(),s),Q={class:"main-container"},I={class:"home-container"},S=v((()=>E("div",{class:"middle"},[E("img",{src:"/dist-dev/assets/grid.9cd0f200.png",alt:""})],-1))),V={class:"bottom"},m=v((()=>E("h2",{style:{"text-align":"center"}},"编程",-1))),A=v((()=>E("h2",{style:{"text-align":"center"}},"控制模式",-1))),C=v((()=>E("h2",{style:{"text-align":"center"}},"主页",-1))),u=v((()=>E("h2",{style:{"text-align":"center"}},"系统安全",-1))),y=v((()=>E("h2",{style:{"text-align":"center"}},"系统状态",-1))),K={class:"control-container"},x=s({setup(s){const r=c(),R=d();e(!1),i({}),a((()=>{}));const v=o((()=>R.state.tagView.controlModeShow));t(v,(s=>{if(s){let s=document.querySelector("div.control-container"),e=document.querySelector("div.home-container");s.style.top=0,s.style.zIndex=10,s.style.visibility="visible",e.style.display="none"}else{let s=document.querySelector("div.control-container"),e=document.querySelector("div.home-container");s.style.visibility="hidden",s.style.top="120%",e.style.display="block"}}));const x=s=>{R.commit("tagView/setLogoShow",!1),"/control"===s?(r.push(s),R.commit("tagView/setControlModeShow",!0)):(r.push(s),R.commit("tagView/setControlModeShow",!1))};return n(((s,e)=>{})),(s,e)=>(g(),l("div",Q,[E("div",I,[S,E("div",V,[E("div",null,[E("img",{class:"mokuaihua",src:"/dist-dev/assets/icon_mokuaihua_nor.4ee7265d.png",alt:"",onClick:e[0]||(e[0]=s=>x("/program"))}),m]),E("div",null,[E("img",{class:"kongzhi",src:"/dist-dev/assets/icon_kongzhi_nor.5631d699.png",alt:"",onClick:e[1]||(e[1]=s=>x("/control"))}),A]),E("div",null,[E("img",{class:"home",src:"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAIQAAACECAYAAABRRIOnAAALLUlEQVR4Xu1dC4yU1RU+ZwCFBW3py9bWplo1Fmpja7SN9pGYpmkqwRbCggqCVMWKj0B3HgtoJhZkWYhaEVvx0RYhIlbbEjSNMabpg8YHTVNE1NrW1mojVrBFWJTH6XdndsvsMrPzP+7/3/vPnj/ZdVzuPef83/nmnPu+TPooAjUIsKKhCNQioIRQPvRDQAmhhFBCKAcaI6ARQtmhEaKCQEGOJ6G5+DSBmE6u/E3oJfzehP9fRd382lDkytCMEHm5DM6+GT/HNHD6bpBiHkhxz1AjxdAiRFnG0F76ISLBxYEczbSO2uhKKvPbgcq3QKGhQ4iinE6HaAN8dloovzFtp+HUTjfxs6HqZbTw0CBESWbTQbodPhoVyU+MuJKja6iL741UP0OVWpsQHTIajvwBUsQMKz7J0RoQ6ypawXusyPNQSOsSoijje1PEOMu4PweStdMy3mZZrhfiWpMQJZmFb/IqINyWCMomhQxDpFjKP0lEvkOhrUWIsrTBVXcgRcxMBdMc/RitkrnohexNRV8KSlqHEJ0yDlFhA8gwPgXcalU8S0cjhSzm7SnrTURdaxAiL5cAnTvwMzoRlJoLNY3Mq2g5r2le1O8S2SaESRE9tBKNx9lewMx0D30Y3dP53OOFPRGMyC4hOuU0OkAP4p0/HeG9k6vCtBXCp2DY+4XklCQnOZuEKMp0tBXM+MKY5KCJIZnJDHVfCVKsiyHFSdVsEWKejKIR9H0Q4XInaIVVynQX7afr6JbspJDsEKJTTu1NEZ8J6xfH5f+EuZApGLN40bEdgdRngxAluRANxzsRGRpNVwd6WWeFmHbD9jnohdzvzIaAiv0mRFlGohdxK8gwJ+D7+F2MMfXehnUWZd7nq6H+EmKRnELvVgaazvAVvEh2Mf0RcyFTMHNqVmd59/hJiJJMxajjaqB1rHeI2THov5gLuQKkeMCOOHtS/CKESRF7KkvbvmPvFT2WxBhd7aH5tJLf8cVKfwixSD6JFPEgUsRnfQEnJTv+AD3taHD+JSV9g6rxgxAlmYIu5d1Y2NqqKWJwXzP9pzK2spzNyKvTxy0hrpGjMX28AmBc7RQFX5Qzlvn1UIfLFOKOECU5qbKiSehMX/zhhR1MWyorsrr4ry7scUOIkkxGL8LseXiPi5fOgM63MLr5bYxuPpy2rekSoixHYUXTckSFa9N+0QzqE7SpVmIgK4+BrHfTsj89QiySE+kdMv3us9J6uRbR8zSW/bSDFC+n8T7pEKIk30KKMHsa3pvGS7Wgjl1IIbORQn6e9LslS4hqiliGFHEdXiRZXUkj5V6+oLF5K51ERZrD+5MyJzknleQT6EU8ADKcnZTxQ1Jujp5EtJhKS/jvSbx/MoQoygUgw49g8NgkjFaZtBPx9lKsyNpoGwu7hLhCRqCVsBRRYb6mCNuuOkKe4C8342SLTpspxB4hivLxSoog+kLiUKiCwwgw/R7RYhq2Fv7DBix2CNEpEzAXYba1vc+GUSojJAJMb2I6fRZ6IZtC1jyieDxCVFPEEqSIDk0RcV0Ru74ZyFqBgawFGLM4EFVadEIslBOwong9yHBOVOVaLwEEmH4HqdPQ4PxnFOnRCFGU89FeMCni/VGUap3EEfg3NMzEdPqjYTWFI0RZhmMLymIoKSA8hasb1jItHw8BQexmDAqOpuvDpJDgTi3Ix2Dh/VDzxXiWau1UEWD6LTY3TcNA1qtB9AYjREm+jrmI+yDwA0GEahnPEGB6A1/kS5BCftnMssEJUU0RN2IMvQiBuWbC9N89RoDR6mPqwnKkG6idDzaytDEhzEmv1RTxZY9fU00LiwDTr1HlwkYn9dYnREm+hhSxFhU/GFafls8EAjswkDUDy/QeG2htf0JskGFY0VdGcFmAgpoiMuHbyEYegodvQgop16aQw4RYIB/B8LNJEV+JrEIrZg+BHP0K0eIinNT7L2N8lRCdci5SxEMgw3HZeyO1ODYCTK+jazoJXdPNDDKcCjJs8fY0lthvqwICIWBOvTmKPseUF3PszUWBKtUWMgMeZiyM6NzQdbVCcghU5zLMOGX4AUSc/s+4SGQHKgfvTRhVOerGrNoi7DJajwbo5OTeTiWHRoDpYfhmKjZNfw+eKoaaYsAAliFEDyqODKj4TZBhJhZjPFIpX5SfKiECIpdWMUOIbq5+SfPyDfw2k5DBRpiZ9hlCPBNoOx3T5t4x8Vf+/25KiLTcHFxPLSFMrflYpjC80ntsntqxjZCphOuGDuK0tMZPdeHFW7SQVg9Y/q2ECO6otEoOJITRa6Yg9mLModlCpmF0OaNwDoXXoHC9a4d2gl0zGy7NUkKk5ebgeuoRoq+2Wep4EAe2S511LIzJyzaa1TswJUgdWJMnOObGXEHEiAdEj4IMi/sGLOpaVBAzdjEpuLVaMnEEBiOEUd4hH0I7sBOfvgnfHQtfP4/Pq9FNwDndDCLEeTRCxEEvmbrNCNFEqxIiGbe4k6qEcIe9l5qVEF66xZ1RSgh32HupWQnhpVvcGaWEcIe9l5qVEF66xZ1RSgh32HupWQnhpVvcGaWEcIe9l5qVEF66xZ1RSgh32HupWQnhpVvcGaWEcIe9l5qVEF66xZ1RSgh32HupWQnhpVvcGaWEcIe9l5qVEF66xZ1RSgh32HupWQnhpVvcGaWEcIe9l5qVEF66xZ1RSgh32HupWQnhpVvcGaWEiIA90y5sYXsCNZ/CdraX8N9dvVLG4u8n4/PZ+Pt5+MnejUBKiBCEYBCAcG9oG21sehdm9QK5iSifz9S9YUqIQIR4Axtcr8VBJ+sDlR5YqCjTcDDKbfhz8JN2IimyUEkJ0QREpq0gw0Qc0vlyLLirtwxuRLQ4PZacpCsrIQZF+AlcD3AB0sPbVvxQljE4u+kXkHWeFXlJCFFCNET1zziQ8/OIDH0NRjvwl2QsDt14EsJOsSPQshQlRF1A96C3cBYO39puGe6quIJ8CqnjaXwanYj8OEKVEHXQw8lZIMOyOLg2rVsQc2VEV9NyaRdQQhyB+Os4s/tEuoV7EvXFPBmFI5f+Bh1+HQethBjgdsaBnd18Q6Jk6BNekBsRJa5PRVdQJUqIIwgxLrG2w0CnVNsSzwX1VSrllBD9YH4V90qZy+LSe/Ji7sf8aHoKm2hSQtQAJPQIreAJqTqnQzahR3N+qjoHU6aE6IfOKkSIq1N1Tl5uh765qepUQgSEm2kp2g/meqj0noKYI4PNQaB+PBohavyQZg+jT61vPQ0lhBKiX2hSQighlBCNsrWmDHOt3uELVCK0alrrrGslhBJiQLhMb9haG5V14o9v1yNohNAIoRFiwBdV2xDay9BehvYyGvcfNEJohNAIoRFCI0SgMRbtZTjuZeTlPjhqeiBnpVFICWFQXoslADOiwh1vpLIg3Zj6zUdVbr2eEsJEiOVYAlCIim08QhRlOra3mSjhx6OEIHxBZ2DV2NqoDolHiKXYxbSTdkD58KgGWK2nhDiArUPHYevizqi4xiOE0VqUexElLo1qgNV6Q50QOdzrvYxj+SI+IRbKCbSftiFUHWPVudGEbUMO3RqtasRa1d3g4yPWtleNaTeNgB1L+JU4QuMTwmjvlInYLfUzfMrFMUbrRkbgEL6Qk9B2MDvTYz12CGFMKMjF+H03DBsZyyKtHA4Bpn2ocBl6FuvCVaxf2h4hjPzvypnYgn8bSHGODeNURhMEmDZXTsbp4i22sLJLiD6rSvJVNDQngxhfwp+Ox0/2Du+yhbBdOeasi9fQTvoNiPAQiPC4XfFmGEMfRaAGASWE0qEfAkoIJYQSQjnQGAGNEMoOjRDKAY0QyoGACPwPcI+p06lhZisAAAAASUVORK5CYII=",alt:"",onClick:e[2]||(e[2]=s=>x("/home"))}),C]),E("div",null,[E("img",{class:"safe",src:"/dist-dev/assets/icon_safe_nor.eba40b75.png",alt:"",onClick:e[3]||(e[3]=s=>x("/safety"))}),u]),E("div",null,[E("img",{class:"state",src:"/dist-dev/assets/icon_state_nor.3c0d433f.png",alt:"",onClick:e[4]||(e[4]=s=>x("/status"))}),y])])]),E("div",K,[h(p)])]))}},[["__scopeId","data-v-cd1e7f63"]]);export{x as default};
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJmaWxlIjoiaW5kZXguZmVmNjM2MTguanMiLCJzb3VyY2VzIjpbIi4uLy4uL3NyYy9hc3NldHMvaW1hZ2UvZ3JpZC5wbmciLCIuLi8uLi9zcmMvdmlld3MvaG9tZS9pbmRleC52dWUiLCIuLi8uLi9zcmMvYXNzZXRzL2ltYWdlL2ljb25fbW9rdWFpaHVhX25vci5wbmciLCIuLi8uLi9zcmMvYXNzZXRzL2ltYWdlL2ljb25fa29uZ3poaV9ub3IucG5nIiwiLi4vLi4vc3JjL2Fzc2V0cy9pbWFnZS9pY29uX2hvbWVfc2VsLnBuZyIsIi4uLy4uL3NyYy9hc3NldHMvaW1hZ2UvaWNvbl9zYWZlX25vci5wbmciLCIuLi8uLi9zcmMvYXNzZXRzL2ltYWdlL2ljb25fc3RhdGVfbm9yLnBuZyJdLCJzb3VyY2VzQ29udGVudCI6WyJleHBvcnQgZGVmYXVsdCBcIl9fVklURV9BU1NFVF9fOWNkMGYyMDBfX1wiIiwiPHRlbXBsYXRlPlxuICA8ZGl2IGNsYXNzPVwibWFpbi1jb250YWluZXJcIj5cbiAgICA8ZGl2IGNsYXNzPVwiaG9tZS1jb250YWluZXJcIj5cbiAgICAgIDxkaXYgY2xhc3M9XCJtaWRkbGVcIj5cbiAgICAgICAgPGltZyBzcmM9XCJAL2Fzc2V0cy9pbWFnZS9ncmlkLnBuZ1wiIGFsdD1cIlwiPlxuICAgICAgPC9kaXY+XG4gICAgICA8ZGl2IGNsYXNzPVwiYm90dG9tXCI+XG4gICAgICAgIDxkaXY+XG4gICAgICAgICAgPGltZyBjbGFzcz1cIm1va3VhaWh1YVwiIHNyYz1cIkAvYXNzZXRzL2ltYWdlL2ljb25fbW9rdWFpaHVhX25vci5wbmdcIiBhbHQ9XCJcIiBAY2xpY2s9XCJyb3V0ZXJDaGFuZ2UoJy9wcm9ncmFtJylcIiAvPlxuICAgICAgICAgIDxoMiBzdHlsZT1cInRleHQtYWxpZ246IGNlbnRlcjtcIj7nvJbnqIs8L2gyPlxuICAgICAgICA8L2Rpdj5cbiAgICAgICAgPGRpdj5cbiAgICAgICAgICA8aW1nIGNsYXNzPVwia29uZ3poaVwiIHNyYz1cIkAvYXNzZXRzL2ltYWdlL2ljb25fa29uZ3poaV9ub3IucG5nXCIgYWx0PVwiXCIgQGNsaWNrPVwicm91dGVyQ2hhbmdlKCcvY29udHJvbCcpXCIgLz5cbiAgICAgICAgICA8aDIgc3R5bGU9XCJ0ZXh0LWFsaWduOiBjZW50ZXI7XCI+5o6n5Yi25qih5byPPC9oMj5cbiAgICAgICAgPC9kaXY+XG4gICAgICAgIDxkaXY+XG4gICAgICAgICAgPGltZyBjbGFzcz1cImhvbWVcIiBzcmM9XCJAL2Fzc2V0cy9pbWFnZS9pY29uX2hvbWVfc2VsLnBuZ1wiIGFsdD1cIlwiIEBjbGljaz1cInJvdXRlckNoYW5nZSgnL2hvbWUnKVwiIC8+XG4gICAgICAgICAgPGgyIHN0eWxlPVwidGV4dC1hbGlnbjogY2VudGVyO1wiPuS4u+mhtTwvaDI+XG4gICAgICAgIDwvZGl2PlxuICAgICAgICA8ZGl2PlxuICAgICAgICAgIDxpbWcgY2xhc3M9XCJzYWZlXCIgc3JjPVwiQC9hc3NldHMvaW1hZ2UvaWNvbl9zYWZlX25vci5wbmdcIiBhbHQ9XCJcIiBAY2xpY2s9XCJyb3V0ZXJDaGFuZ2UoJy9zYWZldHknKVwiIC8+XG4gICAgICAgICAgPGgyIHN0eWxlPVwidGV4dC1hbGlnbjogY2VudGVyO1wiPuezu+e7n+WuieWFqDwvaDI+XG4gICAgICAgIDwvZGl2PlxuICAgICAgICA8ZGl2PlxuICAgICAgICAgIDxpbWcgY2xhc3M9XCJzdGF0ZVwiIHNyYz1cIkAvYXNzZXRzL2ltYWdlL2ljb25fc3RhdGVfbm9yLnBuZ1wiIGFsdD1cIlwiIEBjbGljaz1cInJvdXRlckNoYW5nZSgnL3N0YXR1cycpXCIgLz5cbiAgICAgICAgICA8aDIgc3R5bGU9XCJ0ZXh0LWFsaWduOiBjZW50ZXI7XCI+57O757uf54q25oCBPC9oMj5cbiAgICAgICAgPC9kaXY+XG5cbiAgICAgIDwvZGl2PlxuICAgIDwvZGl2PlxuICAgIDxkaXYgY2xhc3M9XCJjb250cm9sLWNvbnRhaW5lclwiPlxuICAgICAgPGNvbnRyb2xNb2RlPiA8L2NvbnRyb2xNb2RlPlxuICAgIDwvZGl2PlxuXG4gIDwvZGl2PlxuPC90ZW1wbGF0ZT5cblxuPHNjcmlwdCBzZXR1cD5cbmltcG9ydCB7IHJlZiwgb25Nb3VudGVkLCByZWFjdGl2ZSwgY29tcHV0ZWQsIHRvUmF3LCB3YXRjaCwgb25CZWZvcmVVbm1vdW50LCB9IGZyb20gXCJ2dWVcIjtcbmltcG9ydCB7IHVzZVJvdXRlciwgb25CZWZvcmVSb3V0ZUxlYXZlIH0gZnJvbSAndnVlLXJvdXRlcic7XG5pbXBvcnQgeyB1c2VTdG9yZSB9IGZyb20gJ3Z1ZXgnO1xuaW1wb3J0ICogYXMgYXBpIGZyb20gJ0AvYXBpL2luZGV4LmpzJ1xuaW1wb3J0IGNvbnRyb2xNb2RlIGZyb20gXCJAL3ZpZXdzL2NvbnRyb2wvaW5kZXgudnVlXCJcbmNvbnN0IHJvdXRlciA9IHVzZVJvdXRlcigpXG5jb25zdCBzdG9yZSA9IHVzZVN0b3JlKCk7XG5jb25zdCBpc0NvbnRyb2wgPSByZWYoZmFsc2UpXG5jb25zdCBkYXRhID0gcmVhY3RpdmUoe1xuXG59KVxub25Nb3VudGVkKCgpID0+IHtcbiAgLy8gaXNDb250cm9sLnZhbHVlID0gdHJ1ZVxuICAvLyBjb25zb2xlLmxvZyhcIummlumhtVwiLGlzQ29udHJvbC52YWx1ZSk7XG5cbn0pO1xuY29uc3QgY29udHJvbE1vZGVTaG93ID0gY29tcHV0ZWQoKCkgPT4geyByZXR1cm4gc3RvcmUuc3RhdGUudGFnVmlldy5jb250cm9sTW9kZVNob3cgfSAgLy8gIC9ob21lXG4pXG53YXRjaChjb250cm9sTW9kZVNob3csIChuVikgPT4ge1xuICBpZiAoblYpIHtcbiAgICBsZXQgZWxlID0gZG9jdW1lbnQucXVlcnlTZWxlY3RvcignZGl2LmNvbnRyb2wtY29udGFpbmVyJylcbiAgICBsZXQgaG9tZUVsZSA9IGRvY3VtZW50LnF1ZXJ5U2VsZWN0b3IoJ2Rpdi5ob21lLWNvbnRhaW5lcicpXG4gICAgZWxlLnN0eWxlLnRvcCA9IDBcbiAgICBlbGUuc3R5bGUuekluZGV4ID0gMTBcbiAgICBlbGUuc3R5bGUudmlzaWJpbGl0eSA9ICd2aXNpYmxlJ1xuICAgIGhvbWVFbGUuc3R5bGUuZGlzcGxheSA9ICdub25lJ1xuICB9IGVsc2Uge1xuICAgIGxldCBlbGUgPSBkb2N1bWVudC5xdWVyeVNlbGVjdG9yKCdkaXYuY29udHJvbC1jb250YWluZXInKVxuICAgIGxldCBob21lRWxlID0gZG9jdW1lbnQucXVlcnlTZWxlY3RvcignZGl2LmhvbWUtY29udGFpbmVyJylcbiAgICAvL3Zpc2liaWxpdHk6IGhpZGRlblxuICAgIGVsZS5zdHlsZS52aXNpYmlsaXR5ID0gJ2hpZGRlbidcbiAgICBlbGUuc3R5bGUudG9wID0gJzEyMCUnXG4gICAgaG9tZUVsZS5zdHlsZS5kaXNwbGF5ID0gJ2Jsb2NrJ1xuICB9XG59KVxuY29uc3Qgcm91dGVyQ2hhbmdlID0gKHBhdGgpID0+IHtcbiAgc3RvcmUuY29tbWl0KCd0YWdWaWV3L3NldExvZ29TaG93JywgZmFsc2UpO1xuICBpZiAocGF0aCA9PT0gJy9jb250cm9sJykge1xuICAgIC8vIGNvbnNvbGUubG9nKFwicGF0aCA9PT0gJy9jb250cm9sJ1wiKTtcbiAgICByb3V0ZXIucHVzaChwYXRoKVxuICAgIHN0b3JlLmNvbW1pdCgndGFnVmlldy9zZXRDb250cm9sTW9kZVNob3cnLCB0cnVlKTtcbiAgfSBlbHNlIHtcbiAgICByb3V0ZXIucHVzaChwYXRoKVxuICAgIHN0b3JlLmNvbW1pdCgndGFnVmlldy9zZXRDb250cm9sTW9kZVNob3cnLCBmYWxzZSk7XG4gIH1cbn1cblxub25CZWZvcmVSb3V0ZUxlYXZlKCh0bywgZnJvbSkgPT4ge1xuICAvLyBjb25zb2xlLmxvZyh0bywgZnJvbSk7XG4gIC8vIOWcqOWvvOiIquemu+W8gOa4suafk+ivpee7hOS7tueahOWvueW6lOi3r+eUseaXtuiwg+eUqFxuICAvLyDkuI4gYGJlZm9yZVJvdXRlVXBkYXRlYCDkuIDmoLfvvIzlroPlj6/ku6Xorr/pl67nu4Tku7blrp7kvosgYHRoaXNgXG59LClcblxuLy8gb25CZWZvcmVVbm1vdW50KCgpID0+IHtcbi8vICAgY29uc29sZS5sb2coXCLljbPlsIbplIDmr4FcIik7XG4vLyB9KVxuXG48L3NjcmlwdD5cblxuPHN0eWxlIGxhbmc9XCJsZXNzXCIgc2NvcGVkPlxuLm1haW4tY29udGFpbmVyIHtcbiAgd2lkdGg6IDEwMCU7XG4gIGhlaWdodDogMTAwJTtcbiAgcG9zaXRpb246IHJlbGF0aXZlO1xuXG4gIC5ob21lLWNvbnRhaW5lciB7XG4gICAgd2lkdGg6IDEwMCU7XG4gICAgaGVpZ2h0OiAxMDAlO1xuXG4gICAgLm1pZGRsZSB7XG4gICAgICBwb3NpdGlvbjogcmVsYXRpdmU7XG4gICAgICB3aWR0aDogMTAwJTtcbiAgICAgIGhlaWdodDogNzUlO1xuICAgICAgLy8gYmFja2dyb3VuZDogI2ZmZmZmZjtcblxuICAgICAgaW1nIHtcbiAgICAgICAgd2lkdGg6IDEwMCU7XG4gICAgICAgIGhlaWdodDogMTAwJTtcbiAgICAgIH1cblxuXG4gICAgfVxuXG4gICAgLmJvdHRvbSB7XG4gICAgICB3aWR0aDogMTAwJTtcbiAgICAgIGhlaWdodDogMjUlO1xuICAgICAgcGFkZGluZzogMjBweCAxMDBweDtcbiAgICAgIGRpc3BsYXk6IGZsZXg7XG4gICAgICBmbGV4LXdyYXA6IG5vd3JhcDtcbiAgICAgIGp1c3RpZnktY29udGVudDogc3BhY2UtYmV0d2VlbjtcbiAgICAgIGFsaWduLWl0ZW1zOiBjZW50ZXI7XG4gICAgfVxuICB9XG5cbiAgLmNvbnRyb2wtY29udGFpbmVyIHtcbiAgICBwb3NpdGlvbjogYWJzb2x1dGU7XG4gICAgdG9wOiAxMjAlO1xuICAgIGxlZnQ6IDA7XG4gICAgd2lkdGg6IDEwMCU7XG4gICAgaGVpZ2h0OiAxMDAlO1xuICB9XG5cbn08L3N0eWxlPiIsImV4cG9ydCBkZWZhdWx0IFwiX19WSVRFX0FTU0VUX180ZWU3MjY1ZF9fXCIiLCJleHBvcnQgZGVmYXVsdCBcIl9fVklURV9BU1NFVF9fNTYzMWQ2OTlfX1wiIiwiZXhwb3J0IGRlZmF1bHQgXCJkYXRhOmltYWdlL3BuZztiYXNlNjQsaVZCT1J3MEtHZ29BQUFBTlNVaEVVZ0FBQUlRQUFBQ0VDQVlBQUFCUlJJT25BQUFMTFVsRVFWUjRYdTFkQzR5VTFSVStad0NGQlczcHk5YldwbG8xRm1wamE3U045cEdZcG1rcXdSYkNnZ3FDVk1XS2owQjNIZ3RvSmhaa1dZaGFFVnZ4MFJZaElsYmJFalNOTWFicGc4WUhUVk5FMU5yVzFtb2pWckJGV0pUSDZYZG5kc3ZzTXJQelArNy8zL3ZQbmovWmRWenVQZWY4My9ubW5QdStUUG9vQWpVSXNLS2hDTlFpb0lSUVB2UkRRQW1oaEZCQ0tBY2FJNkFSUXRtaEVhS0NRRUdPSjZHNStEU0JtRTZ1L0Uzb0pmemVoUDlmUmQzODJsRGt5dENNRUhtNURNNitHVC9ITkhENmJwQmlIa2h4ejFBanhkQWlSRm5HMEY3NklTTEJ4WUVjemJTTzJ1aEtLdlBiZ2NxM1FLR2hRNGlpbkU2SGFBTjhkbG9vdnpGdHArSFVUamZ4czZIcVpiVHcwQ0JFU1diVFFib2RQaG9WeVUrTXVKS2phNmlMNzQxVVAwT1ZXcHNRSFRJYWp2d0JVc1FNS3o3SjBSb1E2eXBhd1h1c3lQTlFTT3NTb2lqamUxUEVPTXU0UHdlU3RkTXkzbVpacmhmaVdwTVFKWm1GYi9JcUlOeVdDTW9taFF4RHBGaktQMGxFdmtPaHJVV0lzclRCVlhjZ1JjeE1CZE1jL1JpdGtybm9oZXhOUlY4S1NscUhFSjB5RGxGaEE4Z3dQZ1hjYWxVOFMwY2poU3ptN1NuclRVUmRheEFpTDVjQW5UdndNem9SbEpvTE5ZM01xMmc1cjJsZTFPOFMyU2FFU1JFOXRCS054OWxld014MEQzMFkzZFA1M09PRlBSR015QzRoT3VVME9rQVA0cDAvSGVHOWs2dkN0QlhDcDJEWSs0WGtsQ1FuT1p1RUtNcDB0QlhNK01LWTVLQ0pJWm5KREhWZkNWS3NpeUhGU2RWc0VXS2VqS0lSOUgwUTRYSW5hSVZWeW5RWDdhZnI2SmJzcEpEc0VLSlRUdTFORVo4SjZ4Zkg1ZitFdVpBcEdMTjQwYkVkZ2RSbmd4QWx1UkFOeHpzUkdScE5Wd2Q2V1dlRm1IYkQ5am5vaGR6dnpJYUFpdjBtUkZsR29oZHhLOGd3SitENytGMk1NZlhlaG5VV1pkN25xNkgrRW1LUm5FTHZWZ2FhenZBVnZFaDJNZjBSY3lGVE1ITnFWbWQ1OS9oSmlKSk14YWpqYXFCMXJIZUkyVEhvdjVnTHVRS2tlTUNPT0h0Uy9DS0VTUkY3S2t2YnZtUHZGVDJXeEJoZDdhSDV0SkxmOGNWS2Z3aXhTRDZKRlBFZ1VzUm5mUUVuSlR2K0FEM3RhSEQrSlNWOWc2cnhneEFsbVlJdTVkMVkyTnFxS1dKd1h6UDlweksyc3B6TnlLdlR4eTBocnBHak1YMjhBbUJjN1JRRlg1UXpsdm4xVUlmTEZPS09FQ1U1cWJLaVNlaE1YL3poaFIxTVd5b3JzcnI0cnk3c2NVT0lra3hHTDhMc2VYaVBpNWZPZ002M01McjViWXh1UHB5MnJla1NvaXhIWVVYVGNrU0ZhOU4rMFF6cUU3U3BWbUlnSzQrQnJIZlRzajg5UWl5U0Ura2RNdjN1czlKNnVSYlI4elNXL2JTREZDK244VDdwRUtJazMwS0tNSHNhM3B2R1M3V2dqbDFJSWJPUlFuNmU5THNsUzRocWlsaUdGSEVkWGlSWlhVa2o1VjYrb0xGNUs1MUVSWnJEKzVNeUp6a25sZVFUNkVVOEFES2NuWlR4UTFKdWpwNUV0SmhLUy9qdlNieC9Nb1FveWdVZ3c0OWc4TmdrakZhWnRCUHg5bEtzeU5wb0d3dTdoTGhDUnFDVnNCUlJZYjZtQ051dU9rS2U0QzgzNDJTTFRwc3B4QjRoaXZMeFNvb2cra0xpVUtpQ3d3Z3cvUjdSWWhxMkZ2N0RCaXgyQ05FcEV6QVhZYmExdmMrR1VTb2pKQUpNYjJJNmZSWjZJWnRDMWp5aWVEeENWRlBFRXFTSURrMFJjVjBSdTc0WnlGcUJnYXdGR0xNNEVGVmFkRUlzbEJPd29uZzl5SEJPVk9WYUx3RUVtSDRIcWRQUTRQeG5GT25SQ0ZHVTg5RmVNQ25pL1ZHVWFwM0VFZmczTk16RWRQcWpZVFdGSTBSWmhtTUx5bUlvS1NBOGhhc2Ixakl0SHc4QlFleG1EQXFPcHV2RHBKRGdUaTNJeDJEaC9WRHp4WGlXYXUxVUVXRDZMVFkzVGNOQTFxdEI5QVlqUkVtK2pybUkreUR3QTBHRWFoblBFR0I2QTEva1M1QkNmdG5Nc3NFSlVVMFJOMklNdlFpQnVXYkM5Tjg5Um9EUjZtUHF3bktrRzZpZER6YXl0REVoekVtdjFSVHhaWTlmVTAwTGl3RFRyMUhsd2tZbjlkWW5SRW0raGhTeEZoVS9HRmFmbHM4RUFqc3drRFVEeS9RZUcyaHRmMEpza0dGWTBWZEdjRm1BZ3BvaU11SGJ5RVllZ29kdlFnb3AxNmFRdzRSWUlCL0I4TE5KRVYrSnJFSXJaZytCSFAwSzBlSWluTlQ3TDJOOGxSQ2RjaTVTeEVNZ3czSFpleU8xT0RZQ1RLK2phem9KWGRQTkRES2NDakpzOGZZMGx0aHZxd0lDSVdCT3ZUbUtQc2VVRjNQc3pVV0JLdFVXTWdNZVppeU02TnpRZGJWQ2NnaFU1ekxNT0dYNEFVU2Mvcys0U0dRSEtnZnZUUmhWT2VyR3JOb2k3REphandibzVPVGVUaVdIUm9EcFlmaG1LalpOZncrZUtvYWFZc0FBbGlGRUR5cU9ES2o0VFpCaEpoWmpQRklwWDVTZktpRUNJcGRXTVVPSWJxNStTZlB5RGZ3Mms1REJScGlaOWhsQ1BCTm9PeDNUNXQ0eDhWZisvMjVLaUxUY0hGeFBMU0ZNcmZsWXBqQzgwbnRzbnRxeGpaQ3BoT3VHRHVLMHRNWlBkZUhGVzdTUVZnOVkvcTJFQ082b3RFb09KSVRSYTZZZzltTE1vZGxDcG1GME9hTndEb1hYb0hDOWE0ZDJnbDB6R3k3TlVrS2s1ZWJnZXVvUm9xKzJXZXA0RUFlMlM1MTFMSXpKeXphYTFUc3dKVWdkV0pNbk9PYkdYRUhFaUFkRWo0SU1pL3NHTE9wYVZCQXpkakVwdUxWYU1uRUVCaU9FVWQ0aEgwSTdzQk9mdmduZkhRdGZQNC9QcTlGTndEbmREQ0xFZVRSQ3hFRXZtYnJOQ05GRXF4SWlHYmU0azZxRWNJZTlsNXFWRUY2NnhaMVJTZ2gzMkh1cFdRbmhwVnZjR2FXRWNJZTlsNXFWRUY2NnhaMVJTZ2gzMkh1cFdRbmhwVnZjR2FXRWNJZTlsNXFWRUY2NnhaMVJTZ2gzMkh1cFdRbmhwVnZjR2FXRWNJZTlsNXFWRUY2NnhaMVJTZ2gzMkh1cFdRbmhwVnZjR2FXRWNJZTlsNXFWRUY2NnhaMVJTZ2gzMkh1cFdRbmhwVnZjR2FXRWNJZTlsNXFWRUY2NnhaMVJTZ2gzMkh1cFdRbmhwVnZjR2FXRWlJQTkweTVzWVhzQ05aL0NkcmFYOE45ZHZWTEc0dThuNC9QWitQdDUrTW5lalVCS2lCQ0VZQkNBY0c5b0cyMXNlaGRtOVFLNWlTaWZ6OVM5WVVxSVFJUjRBeHRjcjhWQkorc0RsUjVZcUNqVGNEREtiZmh6OEpOMklpbXlVRWtKMFFSRXBxMGd3MFFjMHZseUxMaXJ0d3h1UkxRNFBaYWNwQ3NySVFaRitBbGNEM0FCMHNQYlZ2eFFsakU0dStrWGtIV2VGWGxKQ0ZGQ05FVDF6emlROC9PSURIME5SanZ3bDJRc0R0MTRFc0pPc1NQUXNoUWxSRjFBOTZDM2NCWU8zOXB1R2U2cXVJSjhDcW5qYVh3YW5ZajhPRUtWRUhYUXc4bFpJTU95T0xnMnJWc1FjMlZFVjlOeWFSZFFRaHlCK09zNHMvdEV1b1Y3RXZYRlBCbUZJNWYrQmgxK0hRZXRoQmpnZHNhQm5kMThRNkprNkJOZWtCc1JKYTVQUlZkUUpVcUlJd2d4THJHMncwQ25WTnNTendYMVZTcmxsQkQ5WUg0VjkwcVp5K0xTZS9KaTdzZjhhSG9LbTJoU1F0UUFKUFFJcmVBSnFUcW5RemFoUjNOK3Fqb0hVNmFFNklmT0trU0lxMU4xVGw1dWg3NjVxZXBVUWdTRW0ya3AyZy9tZXFqMG5vS1lJNFBOUWFCK1BCb2hhdnlRWmcralQ2MXZQUTBsaEJLaVgyaFNRaWdobEJDTnNyV21ESE90M3VFTFZDSzBhbHJyckdzbGhCSmlRTGhNYjloYUc1VjE0bzl2MXlOb2hOQUlvUkZpd0JkVjJ4RGF5OUJlaHZZeUd2Y2ZORUpvaE5BSW9SRkNJMFNnTVJidFpUanVaZVRsUGpocWVpQm5wVkZJQ1dGUVhvc2xBRE9pd2gxdnBMSWczWmo2elVkVmJyMmVFc0pFaU9WWUFsQ0lpbTA4UWhSbE9yYTNtU2poeDZPRUlIeEJaMkRWMk5xb0RvbEhpS1hZeGJTVGRrRDU4S2dHV0sybmhEaUFyVVBIWWV2aXpxaTR4aU9FMFZxVWV4RWxMbzFxZ05WNlE1MFFPZHpydll4aitTSStJUmJLQ2JTZnRpRlVIV1BWdWRHRWJVTU8zUnF0YXNSYTFkM2c0eVBXdGxlTmFUZU5nQjFMK0pVNFF1TVR3bWp2bEluWUxmVXpmTXJGTVViclJrYmdFTDZRazlCMk1EdlRZejEyQ0dGTUtNakYrSDAzREJzWnl5S3RIQTRCcG4yb2NCbDZGdXZDVmF4ZjJoNGhqUHp2eXBuWWduOGJTSEdPRGVOVVJoTUVtRFpYVHNicDRpMjJzTEpMaUQ2clN2SlZORFFuZ3hoZndwK094MC8yRHUreWhiQmRPZWFzaTlmUVR2b05pUEFRaVBDNFhmRm1HRU1mUmFBR0FTV0UwcUVmQWtvSUpZUVNRam5RR0FHTkVNb09qUkRLQVkwUXlvR0FDUHdQY0krcDA2bGhaaXNBQUFBQVNVVk9SSzVDWUlJPVwiIiwiZXhwb3J0IGRlZmF1bHQgXCJfX1ZJVEVfQVNTRVRfX2ViYTQwYjc1X19cIiIsImV4cG9ydCBkZWZhdWx0IFwiX19WSVRFX0FTU0VUX18zYzBkNDMzZl9fXCIiXSwibmFtZXMiOlsicm91dGVyIiwidXNlUm91dGVyIiwic3RvcmUiLCJ1c2VTdG9yZSIsInJlZiIsInJlYWN0aXZlIiwib25Nb3VudGVkIiwiY29udHJvbE1vZGVTaG93IiwiY29tcHV0ZWQiLCJzdGF0ZSIsInRhZ1ZpZXciLCJ3YXRjaCIsIm5WIiwiZWxlIiwiZG9jdW1lbnQiLCJxdWVyeVNlbGVjdG9yIiwiaG9tZUVsZSIsInN0eWxlIiwidG9wIiwiekluZGV4IiwidmlzaWJpbGl0eSIsImRpc3BsYXkiLCJyb3V0ZXJDaGFuZ2UiLCJwYXRoIiwiY29tbWl0IiwicHVzaCIsIm9uQmVmb3JlUm91dGVMZWF2ZSIsInRvIiwiZnJvbSJdLCJtYXBwaW5ncyI6IjZLQUFBLG9KQUFlLGlhQzJDZixNQUFNQSxFQUFTQyxJQUNUQyxFQUFRQyxJQUNJQyxHQUFJLEdBQ1RDLEVBQVMsQ0FFdEIsR0FDQUMsR0FBVSxTQUtWLE1BQU1DLEVBQWtCQyxHQUFTLElBQWVOLEVBQU1PLE1BQU1DLFFBQVFILGtCQUU5REksRUFBQUosR0FBa0JLLElBQ3RCLEdBQUlBLEVBQUksQ0FDRixJQUFBQyxFQUFNQyxTQUFTQyxjQUFjLHlCQUM3QkMsRUFBVUYsU0FBU0MsY0FBYyxzQkFDckNGLEVBQUlJLE1BQU1DLElBQU0sRUFDaEJMLEVBQUlJLE1BQU1FLE9BQVMsR0FDbkJOLEVBQUlJLE1BQU1HLFdBQWEsVUFDdkJKLEVBQVFDLE1BQU1JLFFBQVUsTUFDNUIsS0FBUyxDQUNELElBQUFSLEVBQU1DLFNBQVNDLGNBQWMseUJBQzdCQyxFQUFVRixTQUFTQyxjQUFjLHNCQUVyQ0YsRUFBSUksTUFBTUcsV0FBYSxTQUN2QlAsRUFBSUksTUFBTUMsSUFBTSxPQUNoQkYsRUFBUUMsTUFBTUksUUFBVSxPQUN6QixLQUVHLE1BQUFDLEVBQWdCQyxJQUNkckIsRUFBQXNCLE9BQU8sdUJBQXVCLEdBQ3ZCLGFBQVRELEdBRUZ2QixFQUFPeUIsS0FBS0YsR0FDTnJCLEVBQUFzQixPQUFPLDhCQUE4QixLQUUzQ3hCLEVBQU95QixLQUFLRixHQUNOckIsRUFBQXNCLE9BQU8sOEJBQThCLEdBQzVDLFNBR2dCRSxHQUFBLENBQUNDLEVBQUlDLEtBQUwsZ0dDckZKLGlKQ0FBLDRJQ0FBLHE2SENBQSx5SUNBQSJ9
