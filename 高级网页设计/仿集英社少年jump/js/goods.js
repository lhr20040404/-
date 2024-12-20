document.addEventListener("DOMContentLoaded", function () {
    const jsonUrl = "goodsdata.json";
  
    // 获取容器
    const newsList = document.getElementById("news-list");
    const storeList = document.getElementById("store-list");
    const officialSitesList = document.getElementById("official-sites-list");
  
    // 加载 JSON 数据
    fetch(jsonUrl)
      .then(response => {
        if (!response.ok) {
          throw new Error(`HTTP error! Status: ${response.status}`);
        }
        return response.json();
      })
      .then(data => {
        // 渲染新着情報
        data.news.forEach(item => {
          const listItem = document.createElement("li");
          listItem.innerHTML = `
            <a href="${item.link}">
              <img class="list_img pub_img" src="${item.image}" alt="">
              <span class="list_span">
                ${item.title}<br>
                <time class="list_time">${item.date}</time>
              </span>
            </a>
          `;
          newsList.appendChild(listItem);
        });
  
        // 渲染 Jump 商店
        data.stores.forEach(store => {
          const storeItem = document.createElement("li");
          storeItem.innerHTML = `
            <img class="pub_img" src="${store.image}" alt="${store.name}">
            <p class="pub_app_p">${store.name}</p>
            <p class="app_p">${store.description}</p>
          `;
          storeList.appendChild(storeItem);
        });
  
        // 渲染 动画官方网站
        data.official_sites.forEach(site => {
          const siteItem = document.createElement("li");
          siteItem.innerHTML = `
            <img class="pub_img" src="${site.image}" alt="${site.name}">
            <p>${site.name}</p>
          `;
          officialSitesList.appendChild(siteItem);
        });
      })
      .catch(error => console.error("Error fetching JSON data:", error));
  });

  

document.addEventListener('DOMContentLoaded', function () {
    var ticker = document.getElementById('ticker');
    var span = ticker.querySelector('span');

    // 暂停滚动
    function pauseScroll() {
        span.style.animationPlayState = 'paused';
    }

    // 继续滚动
    function resumeScroll() {
        span.style.animationPlayState = 'running';
    }

    // 鼠标悬停时暂停滚动，鼠标离开时继续滚动
    ticker.addEventListener('mouseover', pauseScroll);
    ticker.addEventListener('mouseout', resumeScroll);
});

// navigation.js
document.addEventListener('DOMContentLoaded', function() {
    const navLinks = document.querySelectorAll('.nav-link');
    const currentPath = window.location.pathname;

    navLinks.forEach(link => {
        if (link.href === currentPath) {
            link.classList.add('active');
        }
    });
});