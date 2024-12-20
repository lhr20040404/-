document.addEventListener('DOMContentLoaded', function () {
    const jsonFilePath = 'msg.json';

    fetch(jsonFilePath)
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            if (data.magazines) {
                populateMagazines(data.magazines);
            } else {
                console.error('JSON 数据中没有找到 magazines 数组');
                showError('未找到杂志数据，请稍后重试。');
            }

            if (data.recommendations) {
                populateRecommendations(data.recommendations);
            }

            if (data.comic_awards) {
                populateComicAwards(data.comic_awards);
            }
        })
        .catch(error => {
            console.error('加载 JSON 数据时出错:', error);
            showError('加载数据失败，请检查网络连接或稍后重试。');
        });
});

function populateMagazines(magazines) {
    const zassiLeft = document.getElementById('zassiLeft');
    if (!zassiLeft) {
        console.error('zassiLeft 容器未找到');
        return;
    }

    magazines.forEach(magazine => {
        const magazineDiv = document.createElement('div');
        magazineDiv.className = 'zassi_zu1';

        const detailsHtml = magazine.details.map(detail => `<p>${detail}</p>`).join('');
        const linksHtml = magazine.links.map(link => `<a href="#">${link}</a>`).join('<br>');

        magazineDiv.innerHTML = `
            <img class="pub_img" src="${magazine.image || 'images/placeholder.jpg'}" 
                 alt="${magazine.title || '杂志封面'}">
            <div class="zassi_zu1_text">
                <h1>${magazine.title || '标题缺失'}</h1>
                <p class="jiage">${magazine.price || '价格未知'}</p>
                ${detailsHtml}
                <p>${linksHtml}</p>
            </div>
        `;
        zassiLeft.appendChild(magazineDiv);
    });
}

function populateRecommendations(recommendations) {
    const recommendationsContainer = document.getElementById('recommendations');
    if (!recommendationsContainer) {
        console.error('recommendations 容器未找到');
        return;
    }

    recommendations.forEach(rec => {
        const recDiv = document.createElement('div');
        recDiv.className = 'recommendation';

        recDiv.innerHTML = `
            <img src="${rec.image || 'images/placeholder.jpg'}" alt="${rec.text || '推荐内容'}">
            <p>${rec.text || ''}</p>
            ${rec.link ? `<a href="${rec.link}">查看详情</a>` : ''}
        `;

        recommendationsContainer.appendChild(recDiv);
    });
}

function populateComicAwards(awards) {
    const awardsContainer = document.getElementById('comicAwards');
    if (!awardsContainer) {
        console.error('comicAwards 容器未找到');
        return;
    }

    awards.forEach(award => {
        const awardDiv = document.createElement('div');
        awardDiv.className = 'comic_award';

        awardDiv.innerHTML = `
            <img src="${award.image || 'images/placeholder.jpg'}" alt="${award.text || '奖项内容'}">
            <p>${award.text || ''}</p>
            ${award.link ? `<a href="${award.link}">查看详情</a>` : ''}
        `;

        awardsContainer.appendChild(awardDiv);
    });
}

function showError(message) {
    const zassiLeft = document.getElementById('zassiLeft');
    if (zassiLeft) {
        zassiLeft.innerHTML = `<p>${message}</p>`;
    }
}

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