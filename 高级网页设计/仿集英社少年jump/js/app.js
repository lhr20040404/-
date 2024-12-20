document.addEventListener("DOMContentLoaded", function () {
    // JSON 文件路径
    const jsonUrl = "appdata.json"; // 确保文件路径正确，与你的项目结构一致

    // 获取容器
    const newsList = document.getElementById("news-list");

    // 检查容器是否存在
    if (!newsList) {
        console.error("Error: Element with ID 'news-list' not found.");
        return;
    }

    // 使用 fetch 获取 JSON 数据
    fetch(jsonUrl)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }
            return response.json();
        })
        .then(newsData => {
            // 遍历 JSON 数据并插入到 HTML
            newsData.forEach(item => {
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
        })
        .catch(error => {
            console.error("Error fetching news data:", error);
        });
});

document.addEventListener("DOMContentLoaded", function () {
    console.log("Script loaded, starting fetch...");

    const jsonUrl = "appdata.json";
    const newsList = document.getElementById("news-list");

    if (!newsList) {
        console.error("Error: Element with ID 'news-list' not found.");
        return;
    }

    fetch(jsonUrl)
        .then(response => {
            console.log("Fetch response:", response);
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }
            return response.json();
        })
        .then(newsData => {
            console.log("Fetched data:", newsData);
            newsData.forEach(item => {
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
        })
        .catch(error => {
            console.error("Error fetching news data:", error);
        });
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

window.addEventListener('scroll', function() {
    const returnTopButton = document.getElementById('returnTop');
    if (window.scrollY > 100) {
        returnTopButton.style.display = 'block';
    } else {
        returnTopButton.style.display = 'none';
    }
});

document.getElementById('returnTop').addEventListener('click', function() {
    window.scrollTo({ top: 0, behavior: 'smooth' });
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