/**
 * @Author: Nick Steele <nichlock>
 * @Date:   21:37 Sep 18 2020
 * @Last modified by:   nichlock
 * @Last modified time: 19:08 Sep 19 2020
 */

/* HOW TO USE THIS:
 * Go on the labels page (eg https://github.com/CuUwrRobotics/repo-name/labels)
 * Paste this script in your inspect-element console
 * Press Enter and spam Space until it's done!
 * This will automatically remove the default labels and add the new ones.
 */

var to_remove  = [
{ "name": "bug" },
{ "name": "documentation" },
{ "name": "duplicate" },
{ "name": "enhancement" },
{ "name": "good first issue" },
{ "name": "help wanted" },
{ "name": "invalid" },
{ "name": "question" },
{ "name": "wontfix" },
]

var to_add = [
  {
    "name": "area/documentation",
    "description": "Improvements or additions to documentation",
    "color": "eeeeee"
  },
  {
    "name": "area/github",
    "description": "Related to GitHub setup, not code",
    "color": "eeeeee"
  },
  {
    "name": "area/hardware",
    "description": "Related to the hardware communication or cicuit board",
    "color": "eeeeee"
  },
  {
    "name": "area/machine-vision",
    "description": "Related to machine vision",
    "color": "eeeeee"
  },
  {
    "name": "area/motion",
    "description": "Related to the motion of the robot",
    "color": "eeeeee"
  },
  {
    "name": "area/ros",
    "description": "Related to ROS configurations, builds, installs, etc.",
    "color": "eeeeee"
  },
  {
    "name": "area/docker",
    "description": "Related to Docker image and container configurations, etc.",
    "color": "eeeeee"
  },
  {
    "name": "good first issue",
    "description": "Good for newcomers",
    "color": "0e8a16"
  },
  {
    "name": "help wanted",
    "description": "Extra attention is needed",
    "color": "fbca04"
  },
  {
    "name": "kind/bug",
    "description": "Something isn't working",
    "color": "1d76db"
  },
  {
    "name": "kind/enhancement",
    "description": "Improvement to existing code",
    "color": "1d76db"
  },
  {
    "name": "kind/feature",
    "description": "Features to be added",
    "color": "1d76db"
  },
  {
    "name": "kind/planning",
    "description": "For planning a future development",
    "color": "1d76db"
  },
  {
    "name": "level/advanced",
    "description": "You'll want a good background in programming and/or the package",
    "color": "7fe3e1"
  },
  {
    "name": "level/beginner",
    "description": "Little programming knowledge needed",
    "color": "7fe3e1"
  },
  {
    "name": "level/medium",
    "description": "A little programming knowledge will help, but you won't need any advanced concepts",
    "color": "7fe3e1"
  },
  {
    "name": "question",
    "description": "More info wanted regarding a problem or package",
    "color": "d876e3"
  },
  {
    "name": "vital",
    "description": "Other issues/work rely on this issue",
    "color": "b60205"
  },
  {
    "name": "wontfix",
    "description": "This will not be worked on",
    "color": "000000"
  }
];

to_remove.forEach(function(label) {
  removeLabel(label)
})

to_add.forEach(function(label) {
  addLabel(label)
})

function removeLabel(label) {
  var flag = true;
  to_add.forEach(function(add_label) {
    if(add_label.name === label.name) {
     flag = false
    }
  })
   if(flag) {
  [].slice.call(document.querySelectorAll(".js-labels-list-item"))
  .forEach(function(element) {
    if (element.querySelector('.js-label-link').textContent.trim() === label.name) {
      element.querySelector('.js-delete-label').querySelector(".btn-link").click()
    }
  })
  }
  return flag
}

function updateLabel (label) {
  var flag = false;
  [].slice.call(document.querySelectorAll(".js-labels-list-item"))
  .forEach(function(element) {
    if (element.querySelector('.js-label-link').textContent.trim() === label.name) {
      flag = true
      element.querySelector('.js-edit-label').click()
      element.querySelector('.js-new-label-name-input').value = label.name
      element.querySelector('.js-new-label-description-input').value = label.description
      element.querySelector('.js-new-label-color-input').value = '#' + label.color
      element.querySelector('.js-edit-label-cancel ~ .btn-primary').click()
    }
  })
  return flag
}

function addNewLabel (label) {
  document.querySelector('.js-new-label-name-input').value = label.name
  document.querySelector('.js-new-label-description-input').value = label.description
  document.querySelector('.js-new-label-color-input').value = '#' + label.color
  document.querySelector('.js-details-target ~ .btn-primary').disabled = false
  document.querySelector('.js-details-target ~ .btn-primary').click()
}

function addLabel (label) {
  if (!updateLabel(label)) addNewLabel(label)
}
